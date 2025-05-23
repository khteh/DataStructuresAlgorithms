#pragma once
#include "pch.h"
class Search
{
private:
    void KMPTable(string const &, vector<long> &);

public:
    void KMPSearch(string const &, string const &, vector<size_t> &);
    vector<long> SearchRange(size_t, vector<size_t> const &);
    long BinarySearch(size_t, vector<size_t> const &);
    long BinarySearchMinimum(vector<long> const &data, long, long);
    int BinarySearchCountUpper(vector<long> const &, long, long, long);
    int BinarySearchCountLower(vector<long> const &, long, long, long);
    int BinarySearch(const string &, vector<string> const &);
    bool GridSearch(vector<string> const &, vector<string> const &);
    vector<string> FindShortestPath(int, int, int, int, int);
};