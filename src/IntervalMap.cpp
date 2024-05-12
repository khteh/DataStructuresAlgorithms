#include "stdafx.h"
#include "IntervalMap.h"
template class IntervalMap<int, char>;
template class IntervalMap<size_t, char>;
template class IntervalMap<size_t, string>;
template <typename K, typename V>
IntervalMap<K, V>::IntervalMap()
{
	// constructor associates whole range of K with val by inserting (K_min, val) into the map
	if constexpr (is_integral_v<V>)
		m_map.emplace(numeric_limits<K>::lowest(), numeric_limits<V>::lowest());
	else if constexpr (is_same_v<V, string>)
		m_map.emplace(numeric_limits<K>::lowest(), "");
}
template <typename K, typename V>
IntervalMap<K, V>::IntervalMap(V const &val)
{
	// constructor associates whole range of K with val by inserting (K_min, val) into the map
	m_map.emplace(numeric_limits<K>::lowest(), val);
}

template <typename K, typename V>
IntervalMap<K, V>::~IntervalMap()
{
	m_map.clear();
}
template <typename K, typename V>
size_t IntervalMap<K, V>::size() const noexcept
{
	return m_map.size();
}
template <typename K, typename V>
void IntervalMap<K, V>::clear() noexcept
{
	m_map.clear();
}
template <typename K, typename V>
bool IntervalMap<K, V>::HasKey(K key) const
{
	return m_map.find(key) != m_map.end();
}
template <typename K, typename V>
void IntervalMap<K, V>::print() const
{
	for (typename map<K, V>::const_iterator it = m_map.begin(); it != m_map.end(); it++)
		cout << it->first << ": " << it->second << endl;
	cout << endl;
}
/*
 * Assign value val to interval [keyBegin, keyEnd).
 * Overwrite previous values in this interval.
 * Conforming to the C++ Standard Library conventions, the interval includes keyBegin, but excludes keyEnd.
 * If !( keyBegin < keyEnd ), this designates an empty interval, and assign must do nothing.
 */
template <typename K, typename V>
void IntervalMap<K, V>::emplace(K const &keyBegin, K const &keyEnd, V const &val)
{
	if (keyBegin < keyEnd && keyBegin >= numeric_limits<K>::lowest() && keyEnd <= numeric_limits<K>::max())
	{
		typename map<K, V>::const_iterator it;
		it = m_map.find(keyBegin);
		if (it == m_map.end())
		{
			if (!m_map.empty())
			{
				typename map<K, V>::reverse_iterator rit = m_map.rbegin();
				/*
				 * Check if this is covered by [m_map.end() - 1, m_map.end())
				 * keyBegin = 8
				 * [5, 6, 7]: val
				 */
				if ((keyBegin - 1) == rit->first && val == rit->second)
					return;
				if (keyBegin > numeric_limits<K>::lowest())
				{
					/*
					 * keyBegin = 4
					 * [5, 6, 7]: val
					 */
					it = m_map.upper_bound(keyBegin - 1); // Look for map entry with key > keyBegin - 1
					if (it != m_map.end() && (--it)->second == val)
						return;
				}
			}
		}
		else
		{
			// Existing key range
			if (keyBegin > numeric_limits<K>::lowest())
			{
				for (K key = keyBegin - 1; key > numeric_limits<K>::lowest(); key--)
				{
					it = m_map.upper_bound(key); // Look for map entry with key > 'key'
					if (it != m_map.end())
					{
						if ((--it)->second == val)
							return;
						else
							break;
					}
				}
			}
		}
		for (K i = keyBegin; i < keyEnd; i++)
			m_map[i] = val;
	}
}

// look-up of the value associated with key
template <typename K, typename V>
V const &IntervalMap<K, V>::operator[](K const &key) const
{
	// Look for map entry with key > 'key'
	// [5, 6, 7]: val
	// key: 4: 0
	// key: 8: val
	return (--m_map.upper_bound(key))->second;
}