#include "pch.h"
#include "../src/MPMCCircularBuffer.h"
using namespace std;
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
					while (!buffer.Push(static_cast<long>(producer * ITEMS_PER_PRODUCER + i)))
						this_thread::yield(); });
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
			size_t const producer = static_cast<size_t>(item) / ITEMS_PER_PRODUCER;
			ASSERT_LT(producer, _producers);
			ASSERT_GT(item, last[producer]);
			last[producer] = item;
		}
		all.insert(all.end(), items.begin(), items.end());
	}
	ExpectEachValueOnce(move(all), total);
}
INSTANTIATE_TEST_SUITE_P(
	MPMCCircularBufferTests,
	MPMCCircularBufferConcurrencyTestFixture,
	::testing::Values(make_tuple(1, 1, 2), make_tuple(1, 1, 1024),												// SPSC
					  make_tuple(4, 1, 2), make_tuple(4, 1, 64),												// MPSC
					  make_tuple(1, 4, 2), make_tuple(1, 4, 64),												// SPMC
					  make_tuple(2, 2, 2), make_tuple(4, 4, 8), make_tuple(4, 4, 1024), make_tuple(8, 8, 64))); // MPMC

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
	static constexpr size_t THREADS = 4, ITEMS_PER_PRODUCER = 5000, TOTAL = THREADS * ITEMS_PER_PRODUCER;
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
