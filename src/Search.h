#pragma once
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#ifdef _MSC_VER
#include <ppl.h>
using namespace concurrency;
#elif defined(__GNUC__) || defined(__GNUG__)
#include "oneapi/tbb.h"
using namespace oneapi::tbb;
#endif
using namespace std;

class Search
{
private:
    void KMPTable(string const &, vector<long> &);

public:
    void KMPSearch(string const &, string const &, vector<size_t> &);
    vector<long> SearchRange(size_t, vector<size_t> &);
    size_t BinarySearch(size_t, vector<size_t> &);
    long BinarySearchMinimum(vector<long> &data, long, long);
    int BinarySearchCountUpper(vector<long> &, long, long, long);
    int BinarySearchCountLower(vector<long> &, long, long, long);
    int BinarySearch(const string &, vector<string> &);
    bool GridSearch(vector<string> &, vector<string> &);
};