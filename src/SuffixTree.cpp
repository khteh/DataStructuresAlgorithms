#include "stdafx.h"
#include "SuffixTree.h"
#include <iterator>
void split(const string &s, char delim, vector<size_t> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		size_t i;
		istringstream(item) >> i;
		elems.push_back(i);
	}
}
void splitString(size_t count, const string &s, char delim, set<string> &elems, map<string, size_t> &stringCounts)
{
	stringstream ss(s);
	string item;
	set<string> handled;
	while (std::getline(ss, item, delim))
		if (!item.empty())
		{
			pair<map<string, size_t>::iterator, bool> result = stringCounts.emplace(item, count);
			if (!result.second)
				stringCounts[item] += !handled.count(item) ? count : 1;
			elems.insert(item);
			handled.insert(item);
		}
}
SuffixTree::SuffixTree()
	: _root(make_unique<SuffixTreeNode>(0))
{
}

SuffixTree::SuffixTree(string const &str)
	: SuffixTree()
{
	InsertString(str);
}

SuffixTree::~SuffixTree()
{
	Clear();
}
void SuffixTree::Clear()
{
	_strings.clear();
	_root.reset();
}
size_t SuffixTree::Count() const
{
	return _root ? _root->Count() : 0;
}
void SuffixTree::InsertString(string const &str)
{
	if (!str.empty() && ranges::find(_strings, str) == _strings.end())
	{
		size_t index = 0;
		// First, look for unused index
		for (vector<string>::iterator it = _strings.begin(); it != _strings.end(); it++)
			index += it->size();
		_strings.push_back(str);
		if (!_root)
			_root = make_unique<SuffixTreeNode>(0);
		for (size_t i = 0; i < str.size(); i++)
			_root->InsertString(str.substr(i), index + i);
	}
}
void SuffixTree::RemoveString(string const &str)
{
	_root->RemoveString(str);
}
const vector<size_t> SuffixTree::GetIndexes()
{
	vector<size_t> result;
	set<size_t> tmp = _root->GetIndexes();
	result.assign(tmp.begin(), tmp.end());
	return result;
}
const vector<size_t> SuffixTree::GetIndexes(string const &s)
{
	vector<size_t> result;
	set<size_t> tmp = _root->GetIndexes(s);
	result.assign(tmp.begin(), tmp.end());
	return result;
}
const vector<string> SuffixTree::LongestRepeatedSubstring()
{
	map<size_t, vector<string>> repeats;
	if (!_strings.empty())
	{
		string str;
		str.resize(_strings[0].size());
		map<string, size_t> result = _root->LongestRepeatedSubstring();
		size_t count = 0;
		long index = -1;
		for (map<string, size_t>::iterator it = result.begin(); it != result.end(); it++)
		{
			vector<size_t> tmp;
			::split(it->first, ',', tmp);
			if (it->second >= count)
			{
				count = it->second;
				index = tmp[0];
				repeats[count].push_back(_strings[0].substr(index, count));
			}
		}
		// return index > -1 ? _strings[0].substr(index, count) : "";
	}
	// return "";
	return repeats.empty() ? vector<string>() : repeats.rbegin()->second;
}
/*
 * https://www.hackerrank.com/challenges/substring-diff/problem
 * Unfinished work! Timeout!
 */
const size_t SuffixTree::LongestCommonSubstring(long n)
{
	size_t count = 0;
	if (!_strings.empty())
	{
		map<string, size_t> result = _root->LongestRepeatedSubstring();
		long index1 = -1, index2 = -1;
		for (map<string, size_t>::iterator it = result.begin(); it != result.end(); it++)
		{
			vector<size_t> tmp;
			::split(it->first, ',', tmp);
			if (it->second > count)
			{
				if (tmp.size() == _strings.size())
				{
					count = it->second;
					index1 = tmp[0];
					index2 = tmp[1];
				}
			}
			else
			{ // Look for gap or overlap with the
			}
		}
		// cout << "index: " << index1 << ", count: " << count << endl;
		if (n > 0)
		{
			index2 -= _strings[0].size();
			long start1 = index1 - n >= 0 ? index1 - n : 0;
			long start2 = index2 - n >= 0 ? index2 - n : 0;
			long end1 = index1 + count + (n - (index1 - start1));
			long end2 = index2 + count + (n - (index2 - start2));
			if (end1 > (long)_strings[0].size())
				end1 = _strings[0].size();
			if (end2 > (long)_strings[1].size())
				end2 = _strings[1].size();
			map<size_t, size_t> lengths; // Key: length, Value: start index
			for (;;)
			{
				string s1 = _strings[0].substr(start1, end1 - start1);
				string s2 = _strings[1].substr(start2, end2 - start2);
				long matches = 0 - count;
				for (size_t i = 0; i < min(s1.size(), s2.size()); i++)
					if (s1[i] == s2[i])
						matches++;
				lengths.emplace(count + n + matches, start1);
				bool breakOut = true;
				if (start1 < index1 && end1 < (long)_strings[0].size())
				{
					start1++;
					end1++;
					breakOut = false;
				}
				if (start2 < index2 && end2 < (long)_strings[1].size())
				{
					start2++;
					end2++;
					breakOut = false;
				}
				if (breakOut)
					break;
			}
			map<size_t, size_t>::reverse_iterator it = lengths.rbegin();
			count = it->first;
		}
	}
	return count;
}
SuffixTreeNode::SuffixTreeNode(char c)
	: _char(c)
{
}
SuffixTreeNode::~SuffixTreeNode()
{
	_children.clear();
	_indices.clear();
}
size_t SuffixTreeNode::Count() const
{
	size_t count = _children.size();
	for (map<char, unique_ptr<SuffixTreeNode>>::const_iterator it = _children.begin(); it != _children.end(); it++)
		if (it->second)
			count += it->second->Count();
		else
			throw runtime_error("Bogus node!!!");
	return count;
}
void SuffixTreeNode::InsertString(string const &str, size_t index)
{
	_indices.insert(index);
	if (!str.empty())
	{
		if (!_children.count(str[0]))
			_children.emplace(str[0], make_unique<SuffixTreeNode>(str[0]));
		_children[str[0]]->InsertString(str.substr(1), index);
	}
}
void SuffixTreeNode::RemoveString(string const &str)
{
	if (!str.empty() && _children.count(str[0]))
	{
		_children[str[0]]->RemoveString(str.substr(1));
		_children.erase(str[0]);
	}
}
const set<size_t> SuffixTreeNode::GetIndexes()
{
	return _indices;
}
// Returns the indexes recorded by the last matched charater
const set<size_t> SuffixTreeNode::GetIndexes(string const &str)
{
	set<size_t> result;
	if (str.empty())
		result = _indices; // End of search string. Return indexes of this node.
	else if (_children.count(str[0]))
		result = _children[str[0]]->GetIndexes(str.substr(1));
	return result;
}
const map<string, size_t> SuffixTreeNode::LongestRepeatedSubstring()
{
	// ABABABA
	// Longest Repeated Substring is ABABA. Common suffices are 0, 2
	/*
				root
		A<6> B
		B    A<5>
		A<4> B
		B    A<3>
		A<2> B
		B    A
		A   <1>
	   <0>
	*/
	// aa
	// Longest Repeated Substring is a. Common suffices are 0
	/*
				root
		a<0,1>
		a
	   <0>
	*/
	// aaa
	// Longest Repeated Substring is aa. Common suffices are 0, 1
	/*
				root
		a<0,1,2>
		a<0,1>
		a
	   <0>
	*/
	ostringstream oss;
	ranges::copy(_indices, ostream_iterator<size_t>(oss, ","));
	string indices = oss.str();
	map<string, size_t> result;
	if (_char != '\0' && _indices.size() > 1)
		result.emplace(indices, 1);
	for (map<char, unique_ptr<SuffixTreeNode>>::iterator it = _children.begin(); it != _children.end(); it++)
	{
		map<string, size_t> tmp = it->second->LongestRepeatedSubstring();
		for (map<string, size_t>::iterator it1 = tmp.begin(); it1 != tmp.end(); it1++)
		{
			bool isSamePath = false;
			vector<size_t> indexList;
			::split(it1->first, ',', indexList);
			if (_char != '\0' && indices.size() > it1->first.size())
			{
				for (vector<size_t>::iterator it = indexList.begin(); it != indexList.end(); it++)
					if (_indices.count(*it))
						isSamePath = true;
					else
					{
						isSamePath = false;
						break;
					}
			}
			pair<map<string, size_t>::iterator, bool> tmp1 = result.emplace(it1->first, it1->second);
			if (!tmp1.second && (_char != '\0' || indexList.size() > 1))
				result[it1->first] += it1->second;
			if (_char != '\0' && isSamePath)
				result[it1->first]++;
		}
	}
	return result;
}
