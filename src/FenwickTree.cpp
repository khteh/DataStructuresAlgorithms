#include "FenwickTree.h"
template class FenwickTree<size_t>;
template class FenwickTree<int>;
template class FenwickTree<long>;
template class FenwickTree<long long>;
template <integral_type T>
FenwickTree<T>::FenwickTree(size_t size) : _data(size + 1, T()) {}
template <integral_type T>
FenwickTree<T>::FenwickTree()
{
}
template <integral_type T>
FenwickTree<T>::FenwickTree(vector<T> const &data)
{
    _data.resize(*ranges::max_element(data) + 1);
    for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
        Update(*it, 1);
}
template <integral_type T>
void FenwickTree<T>::Construct(vector<T> const &data)
{
    _data.clear();
    _data.resize(*ranges::max_element(data) + 1);
    for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
        Update(*it, 1);
}
template <integral_type T>
T FenwickTree<T>::lsb(T index)
{
    return index & -index;
}
/*
 * Any time that we move right, add the current value to the counter. OR:
 * Any time you follow a right child link upward, add in the value at the node you arrive at.
[2 1 3 1 2]:
[+2] [+2] [+1]
 1     2    3

         2
        [4]
     1      3
    [2]     [1]
 */
template <integral_type T>
T FenwickTree<T>::Query(T index)
{
    T sum = T();
    for (long long i = index; i > 0; i -= lsb(i))
        sum += _data[i];
    return sum;
}
/*
 Increment the frequency for that node, then start walking up to the root of the tree.
 Any time you follow a link that takes you up as a left child, increment the frequency of the node you encounter by adding in the current value
*/
template <integral_type T>
void FenwickTree<T>::Update(T index, T value)
{
    for (; index < _data.size(); index += lsb(index))
        _data[index] += value;
}
/*
https://www.hackerrank.com/challenges/insertion-sort/problem
100%
[1 1 1 2 2]:
[+3]   [+2]
  1      2
     1
     [+3]
          2
          [+2]
1:
  index = 0
  less = f(1) = 0
  diff = 0
  count = 0
  tree[1] = 1, tree[2] = 1
1:
  index = 1
  less = f(1) = 1
  diff = 0
  count = 1 - 1 = 0
  tree[1] = 2, tree[2] = 2
1:
  index = 2
  less = f(1) = 2
  diff = 0
  count = 0
  tree[1] = 3, tree[2] = 3
2:
  index = 3
  less = f(3) = f(3) + f(2) = 3
  diff = 0
  count = 0
  tree[2] = 4
2:
  index = 4
  less = f(2) = 4
  diff = 0
  count = 0
  tree[2] = 5

[2 1 3 1 2]: -> [1 1 2 2 3]
[+2] [+2] [+1]
 1     2    3

         2
        [4]
     1      3
    [2]     [1]

2:
  index = 0
  less = f(2) = 0
  diff = 0
  count = 0
  tree[2] = 1
1:
  index = 1
  less = f(1) = 0
  diff = 1	[2 1] => [1 2]
  count = 1
  tree[1] = 1, tree[2] = 2
3:
  index = 2
  less = f(3) = f(3) + f(2) = 2
  diff = 0	[1 2 3] => [1 2 3]
  count = 1
  tree[3] = 1
1:
  index = 3
  less = f(1) = 1
  diff = 2	[1 2 3 1] => [1 1 2 3]
  count = 3
  tree[1] = 2, tree[2] = 3
2:
  index = 4
  less = f(2) = 3
  diff = 1	[1 1 2 3 2] => [1 1 2 2 3]
  count = 4
  tree[1] = 2, tree[2] = 4, tree[3] = 1

[4 3 2 1]:
4:
  index = 0
  less = f(4) = 0
  diff = 0
  count = 0
  tree[4] = 1
3:
  index = 1
  less = f(3) = f(3) + f(2) = 0
  diff = 1
  count = 1
  tree[3] = 1, tree[4] = 2
2:
  index = 2
  less = f(2) = 0
  diff = 2
  count = 3
  tree[2] = 1, tree[4] = 3
1:
  index = 3
  less = f(1) = 0
  diff = 3
  count = 6
  tree[1] = 1, tree[2] = 2, tree[4] = 4
 */
template <integral_type T>
size_t FenwickTree<T>::InsertionSortShiftCount(vector<T> const &data)
{
    size_t count = 0, diff = 0, index = 0, sum = 0;
    _data.clear();
    _data.resize(*ranges::max_element(data) + 1);
    for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++, index++)
    {
        sum = Query(*it);
        diff = index - sum;
        count += diff;
        Update(*it, 1);
    }
    return count;
}