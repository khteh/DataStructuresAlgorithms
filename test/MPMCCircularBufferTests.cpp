#include "pch.h"
#include "../src/MPMCCircularBuffer.h"
using namespace std;
// Declared a friend of MPMCCircularBuffer to reach its private memory layout
class MPMCCircularBufferInspector
{
public:
	template <typename T>
	static size_t CacheLineSize(MPMCCircularBuffer<T> const &)
	{
		return MPMCCircularBuffer<T>::CacheLineSize;
	}
	template <typename T>
	static vector<uintptr_t> SlotAddresses(MPMCCircularBuffer<T> const &buffer)
	{
		vector<uintptr_t> addresses;
		for (auto const &slot : buffer._buffer)
			addresses.push_back(reinterpret_cast<uintptr_t>(&slot));
		return addresses;
	}
	template <typename T>
	static size_t DistanceBetweenIndices(MPMCCircularBuffer<T> const &buffer)
	{
		uintptr_t const enqueue = reinterpret_cast<uintptr_t>(&buffer.enqueue_idx_), dequeue = reinterpret_cast<uintptr_t>(&buffer.dequeue_idx_);
		return enqueue > dequeue ? enqueue - dequeue : dequeue - enqueue;
	}
	// Puts an empty buffer in the state it would reach after position items went through it
	template <typename T>
	static void MoveTo(MPMCCircularBuffer<T> &buffer, size_t position)
	{
		buffer.enqueue_idx_.store(position, memory_order_relaxed);
		buffer.dequeue_idx_.store(position, memory_order_relaxed);
		for (size_t i = 0; i < buffer._capacity; i++)
			buffer._buffer[(position + i) & buffer._mask].sequence.store(position + i, memory_order_relaxed);
	}
};
namespace
{
	void WaitFor(atomic<bool> const &start)
	{
		while (!start.load(memory_order_acquire))
			this_thread::yield();
	}
	// Every value in [0, count) was received exactly once
	void ExpectEachValueOnce(vector<long> values, size_t count)
	{
		ranges::sort(values);
		vector<long> expected(count);
		ranges::iota(expected, 0L);
		EXPECT_EQ(expected, values);
	}
	// An item of type T which carries id
	template <typename T>
	T MakeItem(long id)
	{
		if constexpr (is_arithmetic_v<T>)
			return static_cast<T>(id);
		else if constexpr (is_same_v<T, string>)
			return string(32, 'x') + to_string(id); // Long enough to live on the heap
		else if constexpr (is_same_v<T, shared_ptr<long>>)
			return make_shared<long>(id);
		else if constexpr (is_same_v<T, vector<long>>)
			return vector<long>(static_cast<size_t>(1 + id % 8), id);
		else
		{
			T item{};
			memcpy(item.data(), &id, sizeof(id));
			return item;
		}
	}
	// The id carried by item, or -1 if it is corrupted
	template <typename T>
	long ItemId(T const &item)
	{
		if constexpr (is_arithmetic_v<T>)
			return static_cast<long>(item);
		else if constexpr (is_same_v<T, string>)
			return item.size() > 32 && item.starts_with(string(32, 'x')) ? stol(item.substr(32)) : -1;
		else if constexpr (is_same_v<T, shared_ptr<long>>)
			return item ? *item : -1;
		else if constexpr (is_same_v<T, vector<long>>)
		{
			if (item.empty())
				return -1;
			long const id = item.front();
			return item.size() == static_cast<size_t>(1 + id % 8) && ranges::count(item, id) == static_cast<long>(item.size()) ? id : -1;
		}
		else
		{
			long id;
			memcpy(&id, item.data(), sizeof(id));
			return id;
		}
	}
}
// Construction
class MPMCCircularBufferValidCapacityTestFixture : public testing::TestWithParam<size_t>
{
};
TEST_P(MPMCCircularBufferValidCapacityTestFixture, MPMCCircularBufferValidCapacityTests)
{
	ASSERT_NO_THROW(MPMCCircularBuffer<long> buffer(GetParam()));
}
INSTANTIATE_TEST_SUITE_P(
	MPMCCircularBufferTests,
	MPMCCircularBufferValidCapacityTestFixture,
	::testing::Values(2, 4, 8, 64, 1024, 65536));

class MPMCCircularBufferInvalidCapacityTestFixture : public testing::TestWithParam<size_t>
{
};
TEST_P(MPMCCircularBufferInvalidCapacityTestFixture, MPMCCircularBufferInvalidCapacityTests)
{
	ASSERT_THROW(MPMCCircularBuffer<long> buffer(GetParam()), invalid_argument);
}
INSTANTIATE_TEST_SUITE_P(
	MPMCCircularBufferTests,
	MPMCCircularBufferInvalidCapacityTestFixture,
	::testing::Values(0, 1, 3, 5, 6, 7, 9, 12, 100, 1023, 1025));

TEST(MPMCCircularBufferTests, NonCopyableNonMovable)
{
	static_assert(!is_copy_constructible_v<MPMCCircularBuffer<long>>);
	static_assert(!is_copy_assignable_v<MPMCCircularBuffer<long>>);
	static_assert(!is_move_constructible_v<MPMCCircularBuffer<long>>);
	static_assert(!is_move_assignable_v<MPMCCircularBuffer<long>>);
	static_assert(!is_convertible_v<size_t, MPMCCircularBuffer<long>>); // explicit constructor
}
// Single-threaded behaviour for each capacity
class MPMCCircularBufferTestFixture : public testing::TestWithParam<size_t>
{
public:
	void SetUp() override
	{
		_capacity = GetParam();
		_buffer = make_unique<MPMCCircularBuffer<long>>(_capacity);
	}

protected:
	void Fill(long first = 0)
	{
		for (size_t i = 0; i < _capacity; i++)
			ASSERT_TRUE(_buffer->Push(first + static_cast<long>(i)));
	}
	void Drain(long first = 0)
	{
		long value = -1;
		for (size_t i = 0; i < _capacity; i++)
		{
			ASSERT_TRUE(_buffer->Pop(value));
			ASSERT_EQ(first + static_cast<long>(i), value);
		}
	}
	size_t _capacity;
	unique_ptr<MPMCCircularBuffer<long>> _buffer;
};
TEST_P(MPMCCircularBufferTestFixture, PopFromNewBufferFails)
{
	long value = 123;
	ASSERT_FALSE(_buffer->Pop(value));
	ASSERT_EQ(123, value); // The output is not touched
}
TEST_P(MPMCCircularBufferTestFixture, ItemsArePoppedInFIFOOrder)
{
	Fill();
	Drain();
}
TEST_P(MPMCCircularBufferTestFixture, PushToFullBufferFails)
{
	Fill();
	ASSERT_FALSE(_buffer->Push(-1));
	ASSERT_FALSE(_buffer->Push(-2));
	Drain(); // The rejected items did not overwrite anything
}
TEST_P(MPMCCircularBufferTestFixture, PopFromDrainedBufferFails)
{
	Fill();
	Drain();
	long value = 123;
	ASSERT_FALSE(_buffer->Pop(value));
	ASSERT_EQ(123, value);
}
TEST_P(MPMCCircularBufferTestFixture, PopFreesExactlyOneSlot)
{
	Fill();
	long value = -1;
	ASSERT_TRUE(_buffer->Pop(value));
	ASSERT_EQ(0, value);
	ASSERT_TRUE(_buffer->Push(static_cast<long>(_capacity)));
	ASSERT_FALSE(_buffer->Push(-1));
	Drain(1);
}
TEST_P(MPMCCircularBufferTestFixture, RefillsAfterEachLap)
{
	for (long lap = 0; lap < 8; lap++)
	{
		long const first = lap * static_cast<long>(_capacity);
		Fill(first);
		ASSERT_FALSE(_buffer->Push(-1));
		Drain(first);
		long value;
		ASSERT_FALSE(_buffer->Pop(value));
	}
}
TEST_P(MPMCCircularBufferTestFixture, OrderIsKeptAcrossWrapAround)
{
	// Keep the buffer almost full so that the head and the tail both wrap around many times
	long const occupied = static_cast<long>(_capacity) - 1;
	for (long i = 0; i < occupied; i++)
		ASSERT_TRUE(_buffer->Push(i));
	long value = -1;
	for (long i = 0; i < 10 * static_cast<long>(_capacity); i++)
	{
		ASSERT_TRUE(_buffer->Push(occupied + i));
		ASSERT_TRUE(_buffer->Pop(value));
		ASSERT_EQ(i, value);
	}
}
INSTANTIATE_TEST_SUITE_P(
	MPMCCircularBufferTests,
	MPMCCircularBufferTestFixture,
	::testing::Values(2, 4, 8, 64, 1024));

// Non-trivial payload
TEST(MPMCCircularBufferTests, PushCopiesTheItem)
{
	MPMCCircularBuffer<vector<long>> buffer(2);
	vector<long> item{1, 2, 3};
	ASSERT_TRUE(buffer.Push(item));
	ASSERT_EQ(vector<long>({1, 2, 3}), item);
	item[0] = 10; // Must not reach the stored copy
	vector<long> value;
	ASSERT_TRUE(buffer.Pop(value));
	ASSERT_EQ(vector<long>({1, 2, 3}), value);
}
TEST(MPMCCircularBufferTests, PopReplacesTheOutput)
{
	MPMCCircularBuffer<vector<long>> buffer(2);
	ASSERT_TRUE(buffer.Push({1, 2}));
	vector<long> value{7, 8, 9, 10};
	ASSERT_TRUE(buffer.Pop(value));
	ASSERT_EQ(vector<long>({1, 2}), value);
}
TEST(MPMCCircularBufferTests, ReusedSlotsHoldTheNewItem)
{
	MPMCCircularBuffer<vector<long>> buffer(2);
	vector<long> value;
	for (long i = 1; i <= 16; i++)
	{
		vector<long> const item(static_cast<size_t>(i), i);
		ASSERT_TRUE(buffer.Push(item));
		ASSERT_TRUE(buffer.Pop(value));
		ASSERT_EQ(item, value);
	}
}
TEST(MPMCCircularBufferTests, DestructorReleasesUnpoppedItems)
{
	/*
	 * Fails under LeakSanitizer / AddressSanitizer if they are leaked
	 * Passes on correct code. A leak of the unpopped items is reported by LeakSanitizer at process exit, not by an assertion here.
	 */
	MPMCCircularBuffer<vector<long>> buffer(4);
	ASSERT_TRUE(buffer.Push(vector<long>(1024, 1)));
	ASSERT_TRUE(buffer.Push(vector<long>(1024, 2)));
}
// Concurrent behaviour. Parameters: producers, consumers, capacity
class MPMCCircularBufferConcurrencyTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_producers = get<0>(GetParam());
		_consumers = get<1>(GetParam());
		_capacity = get<2>(GetParam());
	}

protected:
	static constexpr size_t ITEMS_PER_PRODUCER = 10000;
	size_t _producers, _consumers, _capacity;
};
TEST_P(MPMCCircularBufferConcurrencyTestFixture, EveryItemIsConsumedOnceAndInProducerOrder)
{
	size_t const total = _producers * ITEMS_PER_PRODUCER;
	MPMCCircularBuffer<long> buffer(_capacity);
	vector<vector<long>> received(_consumers);
	atomic<size_t> consumed{0};
	atomic<bool> start{false};
	{
		vector<jthread> threads;
		for (size_t producer = 0; producer < _producers; producer++)
			threads.emplace_back([&, producer]
								 {
									 WaitFor(start);
									 for (size_t i = 0; i < ITEMS_PER_PRODUCER; i++)
										 /*
										  * producer * ITEMS_PER_PRODUCER + i gives every item a unique number across all producers, so the test can tell afterwards which items arrived and who sent them.
										  * producer is the thread’s number (0, 1, 2…) and i is its item count. Multiplying by ITEMS_PER_PRODUCER (10000) gives each producer its own block of numbers, and i picks the position inside that block:
										  */
										 while (!buffer.Push(static_cast<long>(producer * ITEMS_PER_PRODUCER + i))) // retries the same item until it succeeds, so nothing gets skipped.
											 this_thread::yield();													// lets another thread run between tries, such as a consumer that can free up a slot.
								 });
		for (size_t consumer = 0; consumer < _consumers; consumer++)
			threads.emplace_back([&, consumer]
								 {
				WaitFor(start);
				long value;
				while (consumed.load(memory_order_relaxed) < total)
					if (buffer.Pop(value))
					{
						received[consumer].push_back(value);
						consumed.fetch_add(1, memory_order_relaxed);
					}
					else
						this_thread::yield(); });
		start.store(true, memory_order_release);
	}
	ASSERT_EQ(total, consumed.load());
	long value;
	ASSERT_FALSE(buffer.Pop(value));

	vector<long> all;
	all.reserve(total);
	for (vector<long> const &items : received)
	{
		// Positions only move forward so one consumer sees the items of each producer in the order they were pushed
		vector<long> last(_producers, -1);
		for (long item : items)
		{
			/*
			 * Who sent it check: item / ITEMS_PER_PRODUCER reverses the formula, because integer division drops the remainder. For example, 20005 / 10000 = 2, so producer 2.
			 */
			size_t const producer = static_cast<size_t>(item) / ITEMS_PER_PRODUCER;
			ASSERT_LT(producer, _producers);
			/*
			 * Order check: each producer’s numbers go up as it pushes, so a consumer must see them increasing.
			 */
			ASSERT_GT(item, last[producer]);
			last[producer] = item;
		}
		all.insert(all.end(), items.begin(), items.end());
	}
	/*
	 * Exactly once check:	the blocks join up into 0, 1, 2… up to total − 1 with no gaps. Sorted together, the received values must match that list exactly, so a lost item leaves a gap and a duplicate shows up as an extra.
	 */
	ExpectEachValueOnce(move(all), total);
}
INSTANTIATE_TEST_SUITE_P(
	MPMCCircularBufferTests,
	MPMCCircularBufferConcurrencyTestFixture,
	::testing::Values(make_tuple(1, 1, 2), make_tuple(1, 1, 1024),												// SPSC
					  make_tuple(5, 1, 2), make_tuple(5, 1, 64),												// MPSC
					  make_tuple(1, 5, 2), make_tuple(1, 5, 64),												// SPMC
					  make_tuple(2, 2, 2), make_tuple(5, 5, 8), make_tuple(5, 5, 1024), make_tuple(8, 8, 64))); // MPMC

TEST(MPMCCircularBufferTests, RacingProducersCannotOverfill)
{
	static constexpr size_t CAPACITY = 64, THREADS = 8;
	MPMCCircularBuffer<long> buffer(CAPACITY);
	atomic<size_t> pushed{0};
	atomic<long> next{0};
	atomic<bool> start{false};
	{
		vector<jthread> threads;
		for (size_t i = 0; i < THREADS; i++)
			threads.emplace_back([&]
								 {
				WaitFor(start);
				for (size_t attempt = 0; attempt < CAPACITY; attempt++)
					if (buffer.Push(next.fetch_add(1, memory_order_relaxed)))
						pushed.fetch_add(1, memory_order_relaxed); });
		start.store(true, memory_order_release);
	}
	ASSERT_EQ(CAPACITY, pushed.load());
	// next has moved on for the rejected pushes too so only uniqueness can be checked
	set<long> values;
	long value;
	while (buffer.Pop(value))
		values.insert(value);
	ASSERT_EQ(CAPACITY, values.size());
}
TEST(MPMCCircularBufferTests, RacingConsumersTakeEachItemOnce)
{
	static constexpr size_t CAPACITY = 1024, THREADS = 8;
	MPMCCircularBuffer<long> buffer(CAPACITY);
	for (size_t i = 0; i < CAPACITY; i++)
		ASSERT_TRUE(buffer.Push(static_cast<long>(i)));
	vector<vector<long>> received(THREADS);
	atomic<bool> start{false};
	{
		vector<jthread> threads;
		for (size_t i = 0; i < THREADS; i++)
			threads.emplace_back([&, i]
								 {
				WaitFor(start);
				long value;
				while (buffer.Pop(value))
					received[i].push_back(value); });
		start.store(true, memory_order_release);
	}
	vector<long> all;
	for (vector<long> const &items : received)
		all.insert(all.end(), items.begin(), items.end());
	ExpectEachValueOnce(move(all), CAPACITY);
}
TEST(MPMCCircularBufferTests, ConcurrentHeapPayloadsArriveIntact)
{
	// A slot which is read while it is written, or is handed to two threads, tears or double frees the vector
	static constexpr size_t THREADS = 5, ITEMS_PER_PRODUCER = 5000, TOTAL = THREADS * ITEMS_PER_PRODUCER;
	MPMCCircularBuffer<vector<long>> buffer(8);
	atomic<size_t> consumed{0}, corrupted{0};
	atomic<bool> start{false};
	{
		vector<jthread> threads;
		for (size_t producer = 0; producer < THREADS; producer++)
			threads.emplace_back([&, producer]
								 {
				WaitFor(start);
				for (size_t i = 0; i < ITEMS_PER_PRODUCER; i++)
				{
					long const id = static_cast<long>(producer * ITEMS_PER_PRODUCER + i);
					vector<long> const item(1 + i % 32, id);
					while (!buffer.Push(item))
						this_thread::yield();
				} });
		for (size_t consumer = 0; consumer < THREADS; consumer++)
			threads.emplace_back([&]
								 {
				WaitFor(start);
				vector<long> value;
				while (consumed.load(memory_order_relaxed) < TOTAL)
					if (buffer.Pop(value))
					{
						size_t const expected = 1 + (static_cast<size_t>(value.front()) % ITEMS_PER_PRODUCER) % 32;
						if (value.size() != expected || ranges::count(value, value.front()) != static_cast<long>(expected))
							corrupted.fetch_add(1, memory_order_relaxed);
						consumed.fetch_add(1, memory_order_relaxed);
					}
					else
						this_thread::yield(); });
		start.store(true, memory_order_release);
	}
	ASSERT_EQ(TOTAL, consumed.load());
	ASSERT_EQ(0u, corrupted.load());
}
// Each type below must also be instantiated in MPMCCircularBuffer.cpp
template <typename T>
class MPMCCircularBufferTypedTests : public testing::Test
{
};
using MPMCCircularBufferTypes = testing::Types<int, long, double, string, shared_ptr<long>, vector<long>, array<char, 40>, array<char, 100>>;
TYPED_TEST_SUITE(MPMCCircularBufferTypedTests, MPMCCircularBufferTypes);

TYPED_TEST(MPMCCircularBufferTypedTests, PopFromEmptyBufferLeavesOutputUntouched)
{
	MPMCCircularBuffer<TypeParam> buffer(4);
	TypeParam value = MakeItem<TypeParam>(7);
	ASSERT_FALSE(buffer.Pop(value));
	ASSERT_EQ(7, ItemId(value));
}
TYPED_TEST(MPMCCircularBufferTypedTests, ItemsArePoppedInFIFOOrder)
{
	MPMCCircularBuffer<TypeParam> buffer(8);
	for (long i = 0; i < 8; i++)
		ASSERT_TRUE(buffer.Push(MakeItem<TypeParam>(i)));
	TypeParam value;
	for (long i = 0; i < 8; i++)
	{
		ASSERT_TRUE(buffer.Pop(value));
		ASSERT_EQ(i, ItemId(value));
	}
	ASSERT_FALSE(buffer.Pop(value));
}
TYPED_TEST(MPMCCircularBufferTypedTests, PushToFullBufferFails)
{
	MPMCCircularBuffer<TypeParam> buffer(2);
	ASSERT_TRUE(buffer.Push(MakeItem<TypeParam>(0)));
	ASSERT_TRUE(buffer.Push(MakeItem<TypeParam>(1)));
	ASSERT_FALSE(buffer.Push(MakeItem<TypeParam>(2)));
	TypeParam value;
	ASSERT_TRUE(buffer.Pop(value));
	ASSERT_EQ(0, ItemId(value));
}
TYPED_TEST(MPMCCircularBufferTypedTests, OrderIsKeptAcrossWrapAround)
{
	MPMCCircularBuffer<TypeParam> buffer(4);
	TypeParam value;
	for (long i = 0; i < 3; i++)
		ASSERT_TRUE(buffer.Push(MakeItem<TypeParam>(i)));
	for (long i = 0; i < 40; i++)
	{
		ASSERT_TRUE(buffer.Push(MakeItem<TypeParam>(i + 3)));
		ASSERT_TRUE(buffer.Pop(value));
		ASSERT_EQ(i, ItemId(value));
	}
}
TYPED_TEST(MPMCCircularBufferTypedTests, EveryItemIsConsumedOnceByConcurrentThreads)
{
	static constexpr size_t THREADS = 5, ITEMS_PER_PRODUCER = 2000, TOTAL = THREADS * ITEMS_PER_PRODUCER;
	MPMCCircularBuffer<TypeParam> buffer(8);
	vector<vector<long>> received(THREADS);
	atomic<size_t> consumed{0};
	atomic<bool> start{false};
	{
		vector<jthread> threads;
		for (size_t producer = 0; producer < THREADS; producer++)
			threads.emplace_back([&, producer]
								 {
				WaitFor(start);
				for (size_t i = 0; i < ITEMS_PER_PRODUCER; i++)
				{
					TypeParam const item = MakeItem<TypeParam>(static_cast<long>(producer * ITEMS_PER_PRODUCER + i));
					while (!buffer.Push(item))
						this_thread::yield();
				} });
		for (size_t consumer = 0; consumer < THREADS; consumer++)
			threads.emplace_back([&, consumer]
								 {
				WaitFor(start);
				TypeParam value;
				while (consumed.load(memory_order_relaxed) < TOTAL)
					if (buffer.Pop(value))
					{
						received[consumer].push_back(ItemId(value));
						consumed.fetch_add(1, memory_order_relaxed);
					}
					else
						this_thread::yield(); });
		start.store(true, memory_order_release);
	}
	vector<long> all;
	for (vector<long> const &items : received)
		all.insert(all.end(), items.begin(), items.end());
	ExpectEachValueOnce(move(all), TOTAL);
}
// Memory layout. Whether this makes it faster depends on the machine, so timing is not asserted
TYPED_TEST(MPMCCircularBufferTypedTests, SlotsStartOnCacheLineBoundaries)
{
	MPMCCircularBuffer<TypeParam> buffer(8);
	size_t const line = MPMCCircularBufferInspector::CacheLineSize(buffer);
	for (uintptr_t address : MPMCCircularBufferInspector::SlotAddresses(buffer))
		ASSERT_EQ(0u, address % line);
}
TYPED_TEST(MPMCCircularBufferTypedTests, NeighbouringSlotsDoNotShareACacheLine)
{
	MPMCCircularBuffer<TypeParam> buffer(8);
	size_t const line = MPMCCircularBufferInspector::CacheLineSize(buffer);
	vector<uintptr_t> const addresses = MPMCCircularBufferInspector::SlotAddresses(buffer);
	ASSERT_EQ(8u, addresses.size());
	for (size_t i = 1; i < addresses.size(); i++)
		ASSERT_GE(addresses[i] - addresses[i - 1], line);
}
TEST(MPMCCircularBufferTests, ProducerAndConsumerIndicesDoNotShareACacheLine)
{
	MPMCCircularBuffer<long> buffer(8);
	ASSERT_GE(MPMCCircularBufferInspector::DistanceBetweenIndices(buffer), MPMCCircularBufferInspector::CacheLineSize(buffer));
}
// Counter wrap around, which takes centuries to reach naturally. Parameters: where the counters overflow, capacity
class MPMCCircularBufferCounterWrapTestFixture : public testing::TestWithParam<tuple<size_t, size_t>>
{
public:
	void SetUp() override
	{
		_capacity = get<1>(GetParam());
		_buffer = make_unique<MPMCCircularBuffer<long>>(_capacity);
		MPMCCircularBufferInspector::MoveTo(*_buffer, get<0>(GetParam()) - _capacity / 2); // Half a lap before the overflow
	}

protected:
	size_t _capacity;
	unique_ptr<MPMCCircularBuffer<long>> _buffer;
};
/*
Having several TEST_Ps isn’t wrong in itself: GoogleTest runs every TEST_P of a fixture with every INSTANTIATE_TEST_SUITE_P of that fixture.
*/
TEST_P(MPMCCircularBufferCounterWrapTestFixture, OrderIsKept)
{
	long value = -1;
	for (long i = 0; i < 4 * static_cast<long>(_capacity); i++)
	{
		ASSERT_TRUE(_buffer->Push(i));
		ASSERT_TRUE(_buffer->Pop(value));
		ASSERT_EQ(i, value);
	}
}
TEST_P(MPMCCircularBufferCounterWrapTestFixture, FullAndEmptyAreDetected)
{
	long value = -1;
	for (int lap = 0; lap < 4; lap++)
	{
		ASSERT_FALSE(_buffer->Pop(value));
		for (size_t i = 0; i < _capacity; i++)
			ASSERT_TRUE(_buffer->Push(static_cast<long>(i)));
		ASSERT_FALSE(_buffer->Push(-1));
		for (size_t i = 0; i < _capacity; i++)
		{
			ASSERT_TRUE(_buffer->Pop(value));
			ASSERT_EQ(static_cast<long>(i), value);
		}
	}
}
TEST_P(MPMCCircularBufferCounterWrapTestFixture, EveryItemIsConsumedOnceByConcurrentThreads)
{
	static constexpr size_t THREADS = 5, ITEMS_PER_PRODUCER = 2000, TOTAL = THREADS * ITEMS_PER_PRODUCER;
	vector<vector<long>> received(THREADS);
	atomic<size_t> consumed{0};
	atomic<bool> start{false};
	{
		vector<jthread> threads;
		for (size_t producer = 0; producer < THREADS; producer++)
			threads.emplace_back([&, producer]
								 {
				WaitFor(start);
				for (size_t i = 0; i < ITEMS_PER_PRODUCER; i++)
					while (!_buffer->Push(static_cast<long>(producer * ITEMS_PER_PRODUCER + i)))
						this_thread::yield(); });
		for (size_t consumer = 0; consumer < THREADS; consumer++)
			threads.emplace_back([&, consumer]
								 {
				WaitFor(start);
				long value;
				while (consumed.load(memory_order_relaxed) < TOTAL)
					if (_buffer->Pop(value))
					{
						received[consumer].push_back(value);
						consumed.fetch_add(1, memory_order_relaxed);
					}
					else
						this_thread::yield(); });
		start.store(true, memory_order_release);
	}
	vector<long> all;
	for (vector<long> const &items : received)
		all.insert(all.end(), items.begin(), items.end());
	ExpectEachValueOnce(move(all), TOTAL);
}
INSTANTIATE_TEST_SUITE_P(
	MPMCCircularBufferTests,
	MPMCCircularBufferCounterWrapTestFixture,
	::testing::Combine(::testing::Values(static_cast<size_t>(0), // size_t overflows to 0
										 size_t{1} << 63),		 // The sign of intptr_t flips
					   ::testing::Values<size_t>(2, 8, 1024)));
// Reference counts show what happens to the item, also in builds without the sanitizers
TEST(MPMCCircularBufferTests, PopMovesTheItemOutOfTheSlot)
{
	MPMCCircularBuffer<shared_ptr<long>> buffer(2);
	shared_ptr<long> const item = make_shared<long>(1);
	ASSERT_TRUE(buffer.Push(item));
	ASSERT_EQ(2, item.use_count());
	shared_ptr<long> value;
	ASSERT_TRUE(buffer.Pop(value));
	ASSERT_EQ(2, item.use_count()); // item and value. The slot does not keep a reference
}
TEST(MPMCCircularBufferTests, DestructorReleasesUnpoppedReferences)
{
	shared_ptr<long> const item = make_shared<long>(1);
	{
		MPMCCircularBuffer<shared_ptr<long>> buffer(4);
		ASSERT_TRUE(buffer.Push(item));
		ASSERT_TRUE(buffer.Push(item));
		ASSERT_EQ(3, item.use_count());
	}
	ASSERT_EQ(1, item.use_count());
}
