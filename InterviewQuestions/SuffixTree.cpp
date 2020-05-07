#include "StdAfx.h"
#include "SuffixTree.h"
#include <iterator>
void split(const string& s, char delim, vector<size_t>& elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		size_t i;
		istringstream(item) >> i;
		elems.push_back(i);
	}
}
void splitString(size_t count, const string& s, char delim, set<string>& elems, map<string, size_t>& stringCounts)
{
	stringstream ss(s);
	string item;
	set<string> handled;
	while (std::getline(ss, item, delim))
		if (!item.empty()) {
			pair<map<string, size_t>::iterator, bool> result = stringCounts.emplace(item, count);
			if (!result.second)
				stringCounts[item] += handled.find(item) == handled.end() ? count : 1;
			elems.insert(item);
			handled.insert(item);
		}
}
SuffixTree::SuffixTree()
{
	m_root = make_shared<SuffixTreeNode>(0);
}

SuffixTree::SuffixTree(string const &str)
{
	m_root = make_shared<SuffixTreeNode>(0);
	InsertString(str);
}

SuffixTree::~SuffixTree()
{
	Clear();
}

void SuffixTree::Clear()
{
	m_strings.clear();
	m_root.reset();
}
size_t SuffixTree::Count()
{
	return m_root ? m_root->Count() : 0;
}

void SuffixTree::InsertString(string const &str)
{
	size_t index = 0;
	for (vector<string>::iterator it = m_strings.begin(); it != m_strings.end(); it++)
		index += it->size();
	m_strings.push_back(str);
	if (!m_root)
		m_root = make_shared<SuffixTreeNode>(0);
	for (size_t i = 0; i < str.size(); i++)
		m_root->InsertString(str.substr(i), index + i);
}
void SuffixTree::RemoveString(string const &str)
{
	m_root->RemoveString(str);
}
const vector<size_t> SuffixTree::GetIndexes()
{
	vector<size_t> result;
	set<size_t> tmp = m_root->GetIndexes();
	result.assign(tmp.begin(), tmp.end());
	return result;
}
const vector<size_t> SuffixTree::GetIndexes(string const &s)
{
	vector<size_t> result;
	set<size_t> tmp = m_root->GetIndexes(s);
	result.assign(tmp.begin(), tmp.end());
	return result;
}
const string SuffixTree::LongestRepeatedSubstring()
{
	if (!m_strings.empty()) {
		string str;
		str.resize(m_strings[0].size());
		map<string, size_t> result = m_root->LongestRepeatedSubstring();
		size_t count = 0;
		long index = -1;
		for (map<string, size_t>::iterator it = result.begin(); it != result.end(); it++) {
			vector<size_t> tmp;
			split(it->first, ',', tmp);
			if (it->second > count) {
				count = it->second;
				index = tmp[0];
			}
		}
		return index > -1 ? m_strings[0].substr(index, count) : "";
	}
	return "";
}
const size_t SuffixTree::AnagramSubStrings()
{
	size_t count = 0;
	map<size_t, string> result = m_root->AnagramSubStrings();
	set<string> strings;
	map<string, size_t> stringCount;
	for (map<size_t, string>::iterator it = result.begin(); it != result.end(); it++) {
		//set<string> strings;
		splitString(it->first, it->second, ',', strings, stringCount);
#if 0
		if (!(it->first % 2))
			count += strings.size();
		else  if (!(strings.size() % 2))
			count++; //+= strings.size();
#endif
	}							  
	//return count;
	return result.size() == 1 && result.find(1) != result.end() && strings.find(m_strings[0]) != strings.end() ? 0 : strings.size();
}
const size_t SuffixTree::LongestCommonSubstring(long n)
{
	size_t count = 0;
	if (!m_strings.empty()) {
		map<string, size_t> result = m_root->LongestRepeatedSubstring();
		long index1 = -1, index2 = -1;
		for (map<string, size_t>::iterator it = result.begin(); it != result.end(); it++) {
			vector<size_t> tmp;
			split(it->first, ',', tmp);
			if (it->second > count) {
				if (tmp.size() == m_strings.size()) {
					count = it->second;
					index1 = tmp[0];
					index2 = tmp[1];
				}
			} else { // Look for gap or overlap with the 
			}
		}
		//cout << "index: " << index1 << ", count: " << count << endl;
		if (n > 0) {
			index2 -= m_strings[0].size();
			long start1 = index1 - n >= 0 ? index1 - n : 0;
			long start2 = index2 - n >= 0 ? index2 - n : 0;
			long end1 = index1 + count + (n - (index1 - start1));
			long end2 = index2 + count + (n - (index2 - start2));
			if (end1 > m_strings[0].size())
				end1 = m_strings[0].size();
			if (end2 > m_strings[1].size())
				end2 = m_strings[1].size();
			map<size_t, size_t> lengths; // Key: length, Value: start index
			for (; ; ) {
				string s1 = m_strings[0].substr(start1, end1 - start1);
				string s2 = m_strings[1].substr(start2, end2 - start2);
				long matches = 0 - count;
				for (size_t i = 0; i < min(s1.size(), s2.size()); i++)
					if (s1[i] == s2[i])
						matches++;
				lengths.emplace(count + n + matches, start1);
				bool breakOut = true;
				if (start1 < index1 && end1 < m_strings[0].size()) {
					start1++;
					end1++;
					breakOut = false;
				}
				if (start2 < index2 && end2 < m_strings[1].size()) {
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
	:m_char(c)
{
}
SuffixTreeNode::~SuffixTreeNode()
{
	m_children.clear();
	m_indices.clear();
}
size_t SuffixTreeNode::Count()
{
	size_t count = m_children.size();
	for (map<char, shared_ptr<SuffixTreeNode>>::iterator it = m_children.begin(); it != m_children.end(); it++)
		if (it->second)
			count += it->second->Count();
		else
			throw runtime_error("Bogus node!!!");
	return count;
}
// Amazon
// Neha Aman
void SuffixTreeNode::InsertString(string const &str, size_t index)
{
	m_indices.insert(index);
	if (!str.empty()) {
		pair<map<char, shared_ptr<SuffixTreeNode>>::iterator, bool> result = m_children.emplace(str[0], make_shared<SuffixTreeNode>(str[0]));
		result.first->second->InsertString(str.substr(1), index);
	}
}
void SuffixTreeNode::RemoveString(string const &str)
{
	if (str.length() && m_children.find(str[0]) != m_children.end())
	{
		m_children[str[0]]->RemoveString(str.substr(1));
		m_children.erase(str[0]);
	}
}
const set<size_t> SuffixTreeNode::GetIndexes()
{
	return m_indices;
}
// Returns the indexes recorded by the last matched charater
const set<size_t> SuffixTreeNode::GetIndexes(string const &str)
{
	set<size_t> result;
	if (!str.length())
		result = m_indices; // End of search string. Return indexes of this node.
	if (m_children.find(str[0]) != m_children.end())
		result = m_children[str[0]]->GetIndexes(str.substr(1));
	return result;
}
const map<size_t, string> SuffixTreeNode::AnagramSubStrings()
{
	/*
		 root ('\0')
		m<2> o
		o    m
		m   <1>
		<0>
	*/
	/*
	       root
		a<3> b
		b    b   a
		b    a  <2>
		a   <1>
	   <0>
	*/
	/*
		   root
		c       d <3>
		d d<2>  c
		c       d
		d      <1>
	   <0>
	*/
	string str;
	ostringstream oss;
	map<size_t, string> result;
	if (m_char != '\0')
		str = m_char;
	bool isSplit = false;
	for (map<char, shared_ptr<SuffixTreeNode>>::iterator it = m_children.begin(); it != m_children.end(); it++) {
		map<size_t, string> tmp = it->second->AnagramSubStrings();
		for (map<size_t, string>::iterator it1 = tmp.begin(); it1 != tmp.end(); it1++) {
			isSplit = m_indices.size() != it1->first;
			//oss << (it1->first == m_indices.size() ? str : "") << (result[it1->first] == it1->second ? "," : "") << it1->second;
			oss << (it1->first == m_indices.size() ? str : "") << it1->second << (isSplit ? "," : "");
			result[it1->first].append(oss.str());
			oss.str("");
		}
	}
	if ((m_char != '\0' && result.find(m_indices.size()) == result.end()) || m_children.empty())
		result.emplace(m_indices.size(), str);
#if 0
	else if (result.find(m_indices.size()) != result.end()) {
		oss << "," << str;
		result[m_indices.size()].append(oss.str());
	}
#endif
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
	copy(m_indices.begin(), m_indices.end(), ostream_iterator<size_t>(oss, ","));
	string indices = oss.str();
	map<string, size_t> result;
	if (m_char != '\0' && m_indices.size() > 1)
		result.emplace(indices, 1);
	for (map<char, shared_ptr<SuffixTreeNode>>::iterator it = m_children.begin(); it != m_children.end(); it++) {
		map<string, size_t> tmp = it->second->LongestRepeatedSubstring();
		for (map<string, size_t>::iterator it1 = tmp.begin(); it1 != tmp.end(); it1++) {
			bool isSamePath = false;
			vector<size_t> indexList;
			split(it1->first, ',', indexList);
			if (m_char != '\0' && indices.size() > it1->first.size()) {
				for (vector<size_t>::iterator it = indexList.begin(); it != indexList.end(); it++)
					if (m_indices.find(*it) != m_indices.end())
						isSamePath = true;
					else {
						isSamePath = false;
						break;
					}
			}
			pair<map<string, size_t>::iterator, bool> tmp1 = result.emplace(it1->first, it1->second);
			if (!tmp1.second && (m_char != '\0' || indexList.size() > 1))
				result[it1->first] += it1->second;
			if (m_char != '\0' && isSamePath)
				result[it1->first]++;
		}
	}
	return result;
}