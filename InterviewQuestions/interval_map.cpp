#include "stdafx.h"
#include "interval_map.h"
template class interval_map<int, char>;
template class interval_map<unsigned int, char>;
template<typename K, typename V>
interval_map<K,V>::interval_map(V const& val)
{
	// constructor associates whole range of K with val by inserting (K_min, val) into the map
	m_map.emplace(numeric_limits<K>::lowest(), val);
}

template<typename K, typename V>
interval_map<K,V>::~interval_map()
{
	m_map.clear();
}
template<typename K, typename V>
size_t interval_map<K,V>::size() const noexcept
{
	return m_map.size();
}
template<typename K, typename V>
void interval_map<K, V>::clear() noexcept
{
	m_map.clear();
}
// Assign value val to interval [keyBegin, keyEnd).
// Overwrite previous values in this interval.
// Conforming to the C++ Standard Library conventions, the interval
// includes keyBegin, but excludes keyEnd.
// If !( keyBegin < keyEnd ), this designates an empty interval,
// and assign must do nothing.
template<typename K, typename V>
void interval_map<K, V>::assign(K const& keyBegin, K const& keyEnd, V const& val)
{
	if (keyBegin < keyEnd && keyBegin >= numeric_limits<K>::lowest() && keyEnd <= numeric_limits<K>::max()) {
		map<K, V>::const_iterator it;
		it = m_map.find(keyBegin);
		if (it == m_map.end()) {
			if (!m_map.empty()) {
				auto&[key, value] = *m_map.rbegin();
				if (key == (keyBegin - 1) && value == val)
					return;
				if (keyBegin > numeric_limits<K>::lowest()) {
					it = m_map.upper_bound(keyBegin - 1);
					if (it != m_map.end() && (--it)->second == val)
						return;
				}
			}
		} else {
			if (keyBegin > numeric_limits<K>::lowest()) {
				for (K key = keyBegin - 1; key > numeric_limits<K>::lowest(); key--) {
					it = m_map.upper_bound(key);
					if (it != m_map.end() && (--it)->second == val)
						return;
					else if (it != m_map.end())
						break;
				}
			}
		}
		for (K i = keyBegin; i < keyEnd; i++)
			m_map[i] = val;
	}
}

// look-up of the value associated with key
template<typename K, typename V>
V const& interval_map<K, V>::operator[](K const& key) const {
	return (--m_map.upper_bound(key))->second;
}