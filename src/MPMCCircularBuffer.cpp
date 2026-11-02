#include "MPMCCircularBuffer.h"
// Instantiated in this file as the definitions are not in the header. Node must stay cache-line friendly, see the static_assert in the constructor.
template class MPMCCircularBuffer<long>;
template class MPMCCircularBuffer<vector<long>>;
template <typename T>
MPMCCircularBuffer<T>::MPMCCircularBuffer(size_t capacity)
    : _capacity(capacity),
      _mask(capacity - 1),
      _buffer(capacity)
{
    static_assert((sizeof(Node) % CacheLineSize) == 0 || (CacheLineSize % sizeof(Node)) == 0,
                  "Node layout may lead to destructive cache line sharing");

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
    Node *node;
    size_t pos = enqueue_idx_.load(memory_order_relaxed);

    while (true)
    {
        node = &_buffer[pos & _mask];
        size_t seq = node->sequence.load(memory_order_acquire);
        intptr_t diff = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos);

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
    node->data = data;

    // Pass the baton: hand off ownership to the waiting consumer
    node->sequence.store(pos + 1, memory_order_release);
    return true;
}
template <typename T>
bool MPMCCircularBuffer<T>::Pop(T &value)
{
    Node *node;
    size_t pos = dequeue_idx_.load(memory_order_relaxed);

    while (true)
    {
        node = &_buffer[pos & _mask];
        size_t seq = node->sequence.load(memory_order_acquire);
        intptr_t diff = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos + 1);

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
    value = move(node->data);

    // Reset the baton: hand ownership back to the next producer cycle
    node->sequence.store(pos + _capacity, memory_order_release);
    return true;
}
