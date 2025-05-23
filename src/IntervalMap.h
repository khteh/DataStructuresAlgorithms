#pragma once
using namespace std;
template <typename K, typename V>
class IntervalMap
{
private:
	map<K, V> _map;

public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	IntervalMap();
	IntervalMap(V const &);
	virtual ~IntervalMap();
	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void emplace(K const &, K const &, V const &);
	size_t size() const noexcept;
	void clear() noexcept;
	bool HasKey(K key) const;
	void print() const;
	// look-up of the value associated with key
	V const &
	operator[](K const &) const;
};