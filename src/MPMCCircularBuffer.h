#pragma once
#include "pch.h"
#include "GenericConstraints.h"
using namespace std;

template <typename T>
class MPMCCircularBuffer
{
private:
    struct Node
    {
        T data;
        /*
         The sequence number acts as a state ticket for this specific slot.
         Handles concurrency gracefully by pairing each data slot with an atomic sequence number (or version ticket).
         This technique avoids the notorious ABA problem and eliminates expensive full-buffer scans.
        */
        atomic<size_t> sequence;
    };

// Eliminate false sharing by separating index variables into their own cache lines
#if defined(__cpp_lib_hardware_interference_size)
    static constexpr size_t CacheLineSize = hardware_destructive_interference_size;
#else
    static constexpr size_t CacheLineSize = 64; // Default standard fallback
#endif

    const size_t _capacity;
    const size_t _mask;
    vector<Node> _buffer;

    // Align pointers to prevent performance degradation caused by cache-line bouncing
    alignas(CacheLineSize) atomic<size_t> enqueue_idx_{0};
    alignas(CacheLineSize) atomic<size_t> dequeue_idx_{0};

public:
    explicit MPMCCircularBuffer(size_t);
    ~MPMCCircularBuffer();

    // Non-copyable, non-movable for multi-threaded safety
    MPMCCircularBuffer(const MPMCCircularBuffer &) = delete;
    MPMCCircularBuffer &operator=(const MPMCCircularBuffer &) = delete;

    bool Push(T const &);
    bool Pop(T &);
};
