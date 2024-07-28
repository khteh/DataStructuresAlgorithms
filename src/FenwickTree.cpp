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