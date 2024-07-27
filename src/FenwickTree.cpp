#include "FenwickTree.h"
template class FenwickTree<int>;
template class FenwickTree<long>;
template class FenwickTree<long long>;
template <signed_integral T>
FenwickTree<T>::FenwickTree(size_t size) : _data(size + 1, T()) {}
template <signed_integral T>
FenwickTree<T>::FenwickTree(vector<T> const &data) : _data(data.size() + 1, T())
{
    for (size_t i = 0; i < data.size(); i++)
        Update(i + 1, 1);
}

/*
 * Any time that we move right, add the current value to the counter. OR:
 * Any time you follow a right child link upward, add in the value at the node you arrive at.
 */
template <signed_integral T>
T FenwickTree<T>::Query(T index)
{
    T sum = T();
    for (T i = 0; i > 0; i -= lsb(i))
        sum += _data[i];
    return sum;
}
/*
 Increment the frequency for that node, then start walking up to the root of the tree.
 Any time you follow a link that takes you up as a left child, increment the frequency of the node you encounter by adding in the current value
*/
template <signed_integral T>
void FenwickTree<T>::Update(T index, T value)
{
    for (; index < _data.size(); index += lsb(index))
        _data[index] += value;
}
template <signed_integral T>
T FenwickTree<T>::lsb(T index)
{
    return index & -index;
}