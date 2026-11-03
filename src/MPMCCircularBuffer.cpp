#include "MPMCCircularBuffer.h"
// Instantiated in this file as the definitions are not in the header
template class MPMCCircularBuffer<int>;
template class MPMCCircularBuffer<long>;
template class MPMCCircularBuffer<double>;
template class MPMCCircularBuffer<string>;
template class MPMCCircularBuffer<shared_ptr<long>>;
template class MPMCCircularBuffer<vector<long>>;
template class MPMCCircularBuffer<array<char, 40>>;
template class MPMCCircularBuffer<array<char, 100>>;
/*
On a 64-bit build, effectively zero. I’m working this out from the code and arithmetic, not from a test.

What ABA would take here: the only compare-exchanges are on enqueue_idx_ and dequeue_idx_. For one to wrongly succeed, a thread would have to:

Read pos, check the slot, then get paused just before compare_exchange_weak.
Stay paused while the index advances by exactly a multiple of 2⁶⁴, so it lands back on the same value.
Wake up, and have the stale compare-exchange succeed.

The classic ABA problem comes from a memory address being freed and reused, so a pointer looks unchanged when it isn’t. This class has no such pointers: the indices and sequence numbers only ever count upward, and the slots are never freed while in use. The only way to see the same value twice is for the 64-bit counter to wrap around.

size_t	Operations per second	Time for one full wrap
64-bit	1 billion	About 585 years
32-bit	1 billion	About 4.3 seconds
32-bit	100 million	About 43 seconds

So on 64-bit, one thread would have to stay paused for centuries. The header’s comment that the sequence numbers avoid ABA is fair for x64.

32-bit is different: a thread paused for seconds is unusual but possible. It would still have to resume with the index on exactly the same value, so the odds are very low, but not unthinkable. Your CMakeLists.txt accepts Win32 as well as x64, so the risk applies only if you build that. Also, the diff calculation handles normal counter wraparound correctly, since it subtracts and casts to signed.

A more likely problem: a stalled thread can happen in normal use. If a producer claims a slot and is paused before publishing it, then:

Consumers reach that slot and Pop returns false, even if later slots already hold data.
Once the buffer wraps round to that slot, Push returns false too, so the queue stalls until that thread resumes.

No data is lost or corrupted, and it recovers when the thread wakes. It does mean false doesn’t always mean truly empty or full, and strictly the queue isn’t lock-free in that case. It’s a known trade-off of this design, and it’s why callers need to retry.
*/
template <typename T>
MPMCCircularBuffer<T>::MPMCCircularBuffer(size_t capacity)
    : _capacity(capacity),
      _mask(capacity - 1),
      _buffer(capacity)
{
    /* The buffer capacity MUST be a power of 2 for fast bitwise masking. With 1 slot, the sequence number which hands it to a consumer also hands it to the next producer.
    The bug when capacity is 1: the second Push returns true when it should fail, and two things go wrong:

    The unread 1 is overwritten by 2, so data is silently lost.
    The next Pop never returns. I confirmed this earlier: it hung until a 5-second timeout killed it.

    Why it happens: each slot’s sequence number says whose turn it is. After the first Push, the slot’s number is 1, which means “ready for a consumer”.
    With only one slot, position 1 maps back to that same slot, so the next Push also sees 1 and reads it as “free for me”.
    The two meanings only stay distinct with at least 2 slots, and the constructor accepts capacity 1 anyway because 1 is a power of two.
     */
    if (capacity < 2 || (capacity & _mask) != 0)
        throw invalid_argument("Capacity must be a power of two and at least 2.");

    // Initialize every slot ticket with its linear position index
    for (size_t i = 0; i < _capacity; i++)
        _buffer[i].sequence.store(i, memory_order_relaxed);
}
template <typename T>
MPMCCircularBuffer<T>::~MPMCCircularBuffer()
{
    _buffer.clear();
}
template <typename T>
bool MPMCCircularBuffer<T>::Push(T const &data)
{
    Slot *slot;
    size_t pos = enqueue_idx_.load(memory_order_relaxed);

    while (true)
    {
        slot = &_buffer[pos & _mask];
        size_t seq = slot->sequence.load(memory_order_acquire);
        intptr_t diff = static_cast<intptr_t>(seq - pos); // Subtract while unsigned, which is well defined when the counters wrap around

        if (diff == 0)
        {
            /*
            A producer can only write to a slot if seq == pos. After publishing data, it updates seq to pos + 1
            The slot is empty and ready for this exact sequence turn.
            Try to claim the index before other producer threads do.
            */
            if (enqueue_idx_.compare_exchange_weak(pos, pos + 1, memory_order_relaxed)) // Advance the enqueue index to the next slot for the next producer thread
                break;
        }
        else if (diff < 0)
            // The buffer is completely full
            return false;
        else
            // Another thread beat us; reload the latest index and try again
            pos = enqueue_idx_.load(memory_order_relaxed);
    }

    // Write the data into the safely claimed unique slot
    slot->data = data;

    // Pass the baton: hand off ownership to the waiting consumer
    slot->sequence.store(pos + 1, memory_order_release);
    return true;
}
template <typename T>
bool MPMCCircularBuffer<T>::Pop(T &value)
{
    Slot *slot;
    size_t pos = dequeue_idx_.load(memory_order_relaxed);

    while (true)
    {
        slot = &_buffer[pos & _mask];
        size_t seq = slot->sequence.load(memory_order_acquire);
        intptr_t diff = static_cast<intptr_t>(seq - (pos + 1)); // Subtract while unsigned, which is well defined when the counters wrap around

        if (diff == 0)
        {
            /*
            A consumer can only read from a slot if seq == pos + 1. After consumption, it resets seq to pos + capacity_, making it available for the next production wrap-around lap.
            The slot has data waiting for this specific consumer turn.
            Try to claim the index before other consumer threads do.
            */
            if (dequeue_idx_.compare_exchange_weak(pos, pos + 1, memory_order_relaxed)) // Advance the dequeue index to the next slot for the next consumer thread
                break;
        }
        else if (diff < 0)
            // The buffer is completely empty
            return false;
        else
            // Another consumer beat us; refresh our index view
            pos = dequeue_idx_.load(memory_order_relaxed);
    }

    // Extract the data from the safely claimed slot
    value = move(slot->data);

    // Reset the baton: hand ownership back to the next producer cycle
    slot->sequence.store(pos + _capacity, memory_order_release);
    return true;
}
