#pragma once
#include <map>
#include <limits>
using namespace std;
template<typename K, typename V>
class interval_map
{
private:
	map<K, V> m_map;
public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	interval_map(V const& val);
	virtual ~interval_map();
	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, V const& val);
	size_t size() const noexcept;
	void clear() noexcept;
	// look-up of the value associated with key
	V const& operator[](K const& key) const;
};