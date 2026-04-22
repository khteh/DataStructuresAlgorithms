#include "pch.h"
#include "MaximizeStockProfits.h"
template class MaximizeStockProfits<long>;
/*
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/solutions/108870/most-consistent-ways-of-dealing-with-the-dits/
 * Base cases:
 * T[-1][k][0] = 0, T[-1][k][1] = -Infinity
 * T[i][0][0] = 0, T[i][0][1] = -Infinity
 *
 * T[-1][k] = T[i][0] = 0, that is, no stock or no transaction yield no profit (note the first day has i = 0 so i = -1 means no stock.
 * T[-1][k][1] = T[i][0][1] = -Infinity emphasizes the fact that it is impossible for us to have 1 stock in hand if there is no stock available or no transactions are allowed.
 *
 * Recurrence relations:
 * T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])   Sell
 * T[i][k][1] = max(T[i-1][k][1], T[i-1][k-1][0] - prices[i]) Buy: [k-1] <- The maximum number of allowable transactions decreases by one, since buying on the i-th day will use one transaction,
 *
 * Number of available stocks = length of the prices array.
 */
/* https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * 100%
 * You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
 * K=1
 * T[i][1][0] = max(T[i-1][1][0], T[i-1][1][1] + prices[i])
 * T[i][1][1] = max(T[i-1][1][1], T[i-1][0][0] - prices[i]) = max(T[i-1][1][1], -prices[i])
 */
template <typename T>
T MaximizeStockProfits<T>::MaxProfitK1(vector<T> const &data)
    requires arithmetic_type<T>
{
    T minPrice = numeric_limits<T>::max(), delta = 0;
    for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
    {
        minPrice = min(minPrice, *it);
        delta = max(delta, *it - minPrice);
    }
    return delta;
}
/*
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii
 * Find the maximum profit you can achieve. You may complete at most two transactions.
 * K:2
 * T[i][2][0] = max(T[i-1][2][0], T[i-1][2][1] + prices[i])
 * T[i][2][1] = max(T[i-1][2][1], T[i-1][1][0] - prices[i])
 * T[i][1][0] = max(T[i-1][1][0], T[i-1][1][1] + prices[i])
 * T[i][1][1] = max(T[i-1][1][1], T[i-1][0][0] - prices[i]), T[i-1][0][0] = 0 (No transaction = no profit)
 */
template <typename T>
T MaximizeStockProfits<T>::MaxProfitK2(vector<T> const &data)
    requires arithmetic_type<T>
{
    T T_i10 = 0, T_i20 = 0, T_i11 = numeric_limits<T>::min(), T_i21 = numeric_limits<T>::min();
    for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
    {
        T_i20 = max(T_i20, T_i21 + *it);
        T_i21 = max(T_i21, T_i10 - *it);
        T_i10 = max(T_i10, T_i11 + *it);
        T_i11 = max(T_i11, -*it);
    }
    return T_i20; // Max profit after selling the stock with the most transactions.
}
/*
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
 * 100%
 * On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time. However, you can sell and buy the stock multiple times on the same day, ensuring you never hold more than one share of the stock.
 * K: +Infinity
 * T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])
 * T[i][k][1] = max(T[i-1][k][1], T[i-1][k-1][0] - prices[i]) = max(T[i-1][k][1], T[i-1][k][0] - prices[i])
 *
 * [7,1,5,3,6,4]
 * 5 - 1 = 4
 * 6 - 3 = 3 : profit: 7
 *
 * [1,2,3,4,5]
 * profit: 4
 */
template <typename T>
T MaximizeStockProfits<T>::MaxProfitKInfinity(vector<T> const &prices)
    requires arithmetic_type<T>
{
    long profit = 0, current = prices[0], bought = prices[0];
    for (size_t i = 1; i < prices.size(); i++)
    {
        for (; i < prices.size() && prices[i] >= prices[i - 1]; i++)
            current = prices[i];
        if (current > bought)
            profit += (current - bought);
        if (i < prices.size())
        {
            bought = prices[i];
            current = bought;
        }
    }
    return profit;
}
/*
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv
 * Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.
 * T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])
 * T[i][k][1] = max(T[i-1][k][1], T[i-1][k-1][0] - prices[i]) = max(T[i-1][k][1], T[i-1][k][0] - prices[i])
 * 100%
 */
template <typename T>
T MaximizeStockProfits<T>::MaxProfitKArbitrary(vector<T> const &prices, size_t k)
    requires arithmetic_type<T>
{
    // Max K is buy-sell on alternate days = prices.size() / 2
    if (k >= prices.size() / 2)
        return MaxProfitKInfinity(prices);
    vector<T> T_ik0(k + 1, 0), T_ik1(k + 1, numeric_limits<T>::min());
    for (typename vector<T>::const_iterator it = prices.begin(); it != prices.end(); it++)
        for (size_t i = 1; i <= k; i++)
        {
            T_ik0[i] = max(T_ik0[i], T_ik1[i] + *it);
            T_ik1[i] = max(T_ik1[i], T_ik0[i - 1] - *it);
        }
    return T_ik0[k];
}
/* https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
 * Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
 * After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
 * T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])
 * T[i][k][1] = max(T[i-1][k][1], T[i-2][k][0] - prices[i])
 * 100%
 *
 * State machine of 3 states: (stay, bought, sold). Keep track of amount of profit at every state.
 * stay -> bought -> sold -> stay
 * stay -> stay
 * bought -> bought
 * sold -> stay
 *
 * stay[i] = max(stay[i - 1], sold[i - 1]); // Stay put, or rest from sold state
 * bought[i] = max(bought[i - 1], stay[i - 1] - prices[i]); // Stay put（bought[i - 1], or buy again (stay[i - 1] - prices[i]) - Cannot buy immediately after sell.
 * sold[i] = bought[i - 1] + prices[i]; // Sell - profit = prices[i] - bought[i-1]
 *
 * stay[0] = 0; // At the start, you don't have any stock if you just rest
 * bought[0] = -prices[0]; // After buy, you should have -prices[0] profit. Be positive!
 * sold[0] = 0;

        1  2  3	 0 2
stay:   0  0  1  2 2
bought: -1 -1 -1 1 1
sold:   0  1  2 -1 3
*/
template <typename T>
T MaximizeStockProfits<T>::MaxProfitKInfinityCoolDown(vector<T> const &prices)
    requires arithmetic_type<T>
{
    if (prices.size() < 2)
        return 0;
    T profit = 0;
    vector<T> stay, bought, sold;
    stay.push_back(0);
    bought.push_back(-prices[0]);
    sold.push_back(0);
    for (size_t i = 1; i < prices.size(); i++)
    {
        stay.push_back(max(stay[i - 1], sold[i - 1]));
        bought.push_back(max(bought[i - 1], stay[i - 1] - prices[i]));
        sold.push_back(bought[i - 1] + prices[i]);
    }
    return max(stay.back(), sold.back());
}
/*
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
 * You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
 * The transaction fee is only charged once for each stock purchase and sale.
 * 100%
 *
 * T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])
 * T[i][k][1] = max(T[i-1][k][1], T[i-1][k][0] - prices[i] - fee)
 * or
 * T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i] - fee)
 * T[i][k][1] = max(T[i-1][k][1], T[i-1][k][0] - prices[i])
 */
template <typename T>
T MaximizeStockProfits<T>::MaxProfitKInfinityWithFee(vector<T> const &prices, T fee)
    requires arithmetic_type<T>
{
    T T_ik0 = 0, T_ik1 = numeric_limits<T>::min();
    for (typename vector<T>::const_iterator it = prices.begin(); it != prices.end(); it++)
    {
        T_ik0 = max(T_ik0, T_ik1 + *it); // subtracting fee here will result in integer overflow since T_ik1 is numeric_limits<T>::min();
        T_ik1 = max(T_ik1, T_ik0 - *it - fee);
    }
    return T_ik0;
}
/* https://www.hackerrank.com/challenges/stockmax/problem
 * Each day, you can either buy one share, sell any number of shares that you own, or not make any transaction at all.
 * 100%
 * Max #buys = prices.size() - 1. Max #sells = prices.size() / 2
 * {1, 2, 100} : (100 - 1 = 99) + (100 - 2 = 98) = 197
 *
 * T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])
 * T[i][k][1] = max(T[i-1][k][1], T[i-1][k-1][0] - prices[i]) = max(T[i-1][k][1], T[i-1][k][0] - prices[i])
 *
 * day:0 T_ik0[0] = 0, T_ik1[0] = min(), k:3
 * day:1 *it: 1
 * T_ik0: [0, 0, 0, 0]
 * T_ik1: [min, -1, -1, -1]
 *
 * day:2 *it: 2
 * T_ik0: [0,    1, 1, 1]
 * T_ik1: [min, -2, -1, -1]
 *
 * day:3 *it: 100
 * T_ik0: [0,     98, 99, 99] <- result = 99
 * T_ik1: [min, -100, -2, -1]
 *
 * {1, 3, 1, 2}: (3 - 1 = 2) + (2 - 1 = 1) = 3, k:4
 * day:0 T_ik0[0] = 0, T_ik1[0] = min()
 * day:1 *it: 1
 * T_ik0: [0, 0, 0, 0, 0]
 * T_ik1: [min, -1, -1, -1, -1]
 *
 * day:2 *it: 3
 * T_ik0: [0, 2, 2, 2, 2]
 * T_ik1: [min, -3, -1, -1, -1]
 *
 * day:3 *it: 1
 * T_ik0: [0, 2, 2, 2, 2]
 * T_ik1: [min, -1, 1, 1, 1]
 *
 * day:4 *it: 2
 * T_ik0: [0, 2, 3, 3, 3] <- result = 3
 * T_ik1: [min, -1, 1, 1, 1]
 */
template <typename T>
T MaximizeStockProfits<T>::MaxProfit(vector<T> const &prices)
    requires arithmetic_type<T>
{
    T profit = 0;
    size_t maxIndex = 0;
    for (size_t i = 0; i < prices.size(); i++)
    {
        if (maxIndex <= i)
        {
            typename vector<T>::const_iterator peak = ranges::max_element(prices.begin() + i, prices.end());
            if (peak != prices.end())
                maxIndex = distance(prices.begin(), peak);
        }
        if (maxIndex > i)
        {
            // cout << "Profit: " << *peak - prices[i] << endl;
            profit += prices[maxIndex] - prices[i];
        }
    }
    return profit;
#if 0
    T T_ik0 = 0, T_ik1 = numeric_limits<T>::min();
    for (typename vector<T>::const_iterator it = prices.begin(); it != prices.end(); it++)
    {
        T prev_T_ik0 = T_ik0;
        // T_ik0 = max(T_ik0, T_ik1 + *it);      // Sell
        T_ik0 += max(T_ik0, T_ik1 + *it);     // Sell
        T_ik1 = max(T_ik1, prev_T_ik0 - *it); // Buy
    }
    return T_ik0;
    size_t k = prices.size();
    vector<T> T_ik0(k + 1, 0), T_ik1(k + 1, numeric_limits<T>::min());
    for (typename vector<T>::const_iterator it = prices.begin(); it != prices.end(); it++)
        for (size_t i = 1; i <= k; i++)
        {
            T_ik0[i] = max(T_ik0[i], T_ik1[i] + *it);
            T_ik1[i] = max(T_ik1[i], T_ik0[i - 1] - *it); // Buy: [k-1] <- The maximum number of allowable transactions decreases by one, since buying on the i-th day will use one transaction,
        }
    return T_ik0[k];
#endif
}
