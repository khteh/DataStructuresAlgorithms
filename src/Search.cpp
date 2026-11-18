#include "pch.h"
#include "Search.h"
/* https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 * https://cp-algorithms.com/string/prefix-function.html
 */
void Search::_KMPTable(string const& w, vector<long>& T)
{
    // the first few values are fixed but different from what the algorithm might suggest
    T.resize(w.size() + 1);
    T[0] = -1;
    long pos = 1, cnd = 0;
    for (; pos < (long)w.size(); pos++, cnd++)
    {
        if (w[pos] == w[cnd])
            T[pos] = T[cnd];
        else
        {
            T[pos] = cnd;
            cnd = T[cnd]; // To increase performance
            for (; cnd >= 0 && w[pos] != w[cnd]; cnd = T[cnd])
                ;
        }
    }
    T[pos] = cnd; // (only needed when all word occurrences are searched)
}
void Search::KMPSearch(string const& s, string const& w, vector<size_t>& result)
{
    vector<long> T;
    _KMPTable(w, T);
    for (long j = 0, k = 0; j < (long)s.size();)
    {
        if (w[k] == s[j])
        {
            j++;
            k++;
            if (k == w.size())
            {
                // (occurrence found, if only first occurrence is needed, m ← j - k  may be returned here)
                result.push_back(j - k);
                k = T[k]; // (T[length(W)] can't be -1)
            }
        }
        else
        {
            k = T[k];
            if (k < 0)
            {
                j++;
                k++;
            }
        }
    }
}
/* https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 * 100%
 */
vector<long> Search::SearchRange(size_t target, vector<size_t> const& nums)
{
    long start = 0, end = nums.size() - 1, middle = end / 2 + end % 2;
    vector<long> result{ -1, -1 }; // result[0] = start (inclusive); result[1] = end (exclusive)
    if (nums.empty())
        return result;
    for (; start <= end && (result[0] == -1 || result[1] == -1);)
    {
        if (target > nums[start] && target < nums[middle])
        {
            size_t data = nums[middle - 1];
            for (end = middle - 1; end >= start && nums[end] == data; end--)
                ;
            if (start > end)
                return result;
            end++;
            middle = start + (end - start) / 2 + (end - start) % 2;
        }
        else if (target > nums[middle] && target < nums[end])
        {
            size_t data = nums[middle + 1];
            for (start = middle + 1; start <= end && nums[start] == data; start++)
                ;
            if (start > end)
                return result;
            start--;
            middle = start + (end - start) / 2 + (end - start) % 2;
        }
        else if (target < nums[start] || target > nums[end])
            return result;
        long index = -1;
        if (target == nums[start])
            index = start;
        else if (target == nums[end])
            index = end;
        else if (target == nums[middle])
            index = middle;
        if (index > -1)
        {
            for (start = index; start >= 0 && nums[start] == target; start--)
                result[0] = start;
            for (end = index; end < (long)nums.size() && nums[end] == target; end++)
                result[1] = end;
        }
    }
    return result;
}
/* Binary Search (http://en.wikipedia.org/wiki/Binary_search_algorithm)
 * Dichotomic Divide And Conquer: O(Log n). In case of duplicates, the algorithm drops to linear search O(n)
 * Assumption: source is sorted in increasing order and rotated a number of times
 * Ex: Input: find 5 in array (15 16 19 20 25 1 3 4 5 7 10 14)
 *			                   L             M              U
 * 4 8 9 9 9 10 12 13 1 2 2 3
 * L            M           U
 * https://leetcode.com/problems/search-in-rotated-sorted-array/
 * 100%
 */
long Search::BinarySearch(size_t toSearch, vector<size_t> const& data)
{
    for (size_t lower = 0, middle = 0, upper = data.size() - 1; lower <= upper;)
    {
        middle = lower + (upper - lower) / 2 + (upper - lower) % 2;
        if (toSearch == data[middle])
            return middle;
        else if (toSearch == data[lower])
            return lower;
        else if (toSearch == data[upper])
            return upper;
        else if (data[lower] <= data[middle])
        {
            // 5 6 7 8 1 2 3
            // L     M     U
            if (toSearch > data[lower] && toSearch < data[middle]) // Ex: toSearch=7
                upper = middle - 1;
            else // Ex: toSearch=2
                lower = middle + 1;
        }
        else
        { // Lower >= Middle
            // 6 7 8 9 1 2 3 4 5
            // L       M       U
            if (toSearch > data[middle] && toSearch < data[upper]) // Ex: toSearch=3
                lower = middle + 1;
            else // Ex: toSearch=8
                upper = middle - 1;
        }
    }
    return -1;
}

/* https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
 * 100%
 */
long Search::BinarySearchMinimum(vector<long> const& data, long start, long end)
{
    if (start == end)
        return data[start];
    else if (end - start == 1)
        return min(data[start], data[end]);
    else if (start < end)
    {
        size_t middle = start + (end - start) / 2 + (end - start) % 2;
        long data1 = BinarySearchMinimum(data, start, middle - 1);
        long data2 = BinarySearchMinimum(data, middle + 1, end);
        return min(data[middle], min(data1, data2));
    }
    return numeric_limits<long>::min();
}
/*
 * Binary search for the upper bound of sorted list with duplicate items.
 * Returns the last index of the repeated items found in the sorted list
 */
int Search::BinarySearchCountUpper(vector<long> const& source, long toSearch, long start, long end)
{
    int mid = start + (end - start) / 2 + (end - start) % 2;
    if (end < start)
        return 0;
    if (source[mid] == toSearch && (mid == end || source[mid + 1] != toSearch))
        // 1 2 3 4 [4] 5
        return mid;
    else if (source[mid] <= toSearch)
        // 1 2 3 [3] 4 4 4 (toSearch: 4)
        return BinarySearchCountUpper(source, toSearch, mid + 1, end);
    else
        // 1 2 3 [4] 4 4 (toSearch: 3)
        return BinarySearchCountUpper(source, toSearch, start, mid - 1);
}
/*
 * Binary search for the lower bound of sorted list with duplicate items.
 * Returns the first index of the repeated items found in the sorted list
 */
int Search::BinarySearchCountLower(vector<long> const& source, long toSearch, long start, long end)
{
    int mid = start + (end - start) / 2 + (end - start) % 2;
    if (end < start)
        return 0;
    if (source[mid] == toSearch && (mid == start || source[mid - 1] != toSearch))
        // 1 [2] 2 3 4 5
        return mid;
    else if (source[mid] < toSearch)
        // 1 2 3 [3] 4 4 4 (toSearch: 4)
        return BinarySearchCountLower(source, toSearch, mid + 1, end);
    else
        return BinarySearchCountLower(source, toSearch, start, mid - 1);
}
int Search::BinarySearch(const string& toSearch, vector<string> const& source)
{
    for (int lower = 0, upper = source.size() - 1, middle = 0; lower <= upper;)
    {
        while (lower <= upper && source[upper].empty())
            upper--;
        if (lower > upper)
            return -1;
        middle = lower + (upper - lower) / 2 + (upper - lower) % 2;
        while (source[middle].empty())
            middle++;
        if (source[middle] == toSearch)
            return middle;
        else if (toSearch < source[middle])
            upper = middle - 1;
        else
            lower = middle + 1;
    }
    return -1;
}
/* https://www.hackerrank.com/challenges/the-grid-search/problem
 * 100%
 */
bool Search::GridSearch(vector<string> const& pattern, vector<string> const& grid)
{
    size_t i = 0;
    size_t found = 0;
    set<size_t> locations;
    for (size_t j = 0; j < grid.size() && i < pattern.size();)
    {
        bool resetI = false;
        set<size_t> locations1;
        for (size_t offset = 0, tmp = 0; offset < grid[j].size() && tmp != string::npos; offset++)
        {
            tmp = grid[j].find(pattern[i], offset);
            if (tmp != string::npos)
                locations1.insert(tmp);
        }
        if (locations1.empty() && !locations.empty())
        {
            locations.clear();
            found = 0;
            i = 0;
            resetI = true;
        }
        else if (!locations1.empty() && locations.empty())
            locations = move(locations1);
        else if (!locations1.empty() && !locations.empty())
        {
            set<size_t> intersections;
            set_intersection(locations1.begin(), locations1.end(), locations.begin(), locations.end(), inserter(intersections, intersections.begin()));
            if (intersections.empty())
            {
                locations.clear();
                found = 0;
                i = 0;
                resetI = true;
            }
            else
                locations = move(intersections);
        }
        if (!locations.empty())
        {
            found++;
            i++;
        }
        if (!resetI) // Do not advance row if we have to search for pattern from the start of the pattern block
            j++;
    }
    return i == pattern.size() && found == pattern.size();
}
/* https://www.hackerrank.com/challenges/red-knights-shortest-path/problem
 * 100%
 */
vector<string> Search::FindShortestPath(int n, int i_start, int j_start, int i_end, int j_end)
{
    vector<string> result;
    ostringstream oss;
    // Print the distance along with the sequence of moves.
    // UL, UR, R, LR, LL, L.
    size_t diff_i = abs(i_end - i_start), diff_j = abs(j_end - j_start);
    // Upper Left
    if (i_end < i_start && j_end < j_start)
    {
        if ((i_start - i_end) % 2)
        {
            result.push_back("Impossible");
            return result;
        }
        long uls = (i_start - i_end) / 2; // 6 / 2 = 3
        long dest_j = j_start - uls;      // 6 - 3 = 3
        if ((abs(j_end - dest_j)) % 2)
        {
            result.push_back("Impossible");
            return result;
        }
        long L = (dest_j - j_end) / 2;
        oss << uls + L;
        result.push_back(oss.str());
        oss.str("");
        for (size_t i = 0; i < (size_t)uls; i++)
        {
            oss << "UL";
            if (i != uls - 1)
                oss << " ";
        }
        if (L)
            oss << " ";
        for (size_t i = 0; i < (size_t)L; i++)
        {
            oss << "L";
            if ((long)i < L - 1)
                oss << " ";
        }
    }
    // Upper Right
    else if (i_end < i_start && j_end > j_start)
    {
        if ((i_start - i_end) % 2)
        {
            result.push_back("Impossible");
            return result;
        }
        int urs = (i_start - i_end) / 2; // 4 / 2 = 2
        int dest_j = j_start + urs;      // 2 - 1 = 1
        if ((abs(j_end - dest_j)) % 2)
        {
            result.push_back("Impossible");
            return result;
        }
        int R = (j_end - dest_j) / 2; // (3 -
        oss << urs + R;
        result.push_back(oss.str());
        oss.str("");
        for (size_t i = 0; i < (size_t)urs; i++)
        {
            oss << "UR";
            if ((long)i != urs - 1)
                oss << " ";
        }
        if (R)
            oss << " ";
        for (size_t i = 0; i < (size_t)R; i++)
        {
            oss << "R";
            if ((long)i < R - 1)
                oss << " ";
        }
    }
    // Lower Left
    else if (i_end > i_start && j_end < j_start)
    {
        if ((i_end - i_start) % 2)
        {
            result.push_back("Impossible");
            return result;
        }
        int lls = (i_end - i_start) / 2;
        int dest_j = j_start - lls;
        if ((abs(j_end - dest_j)) % 2)
        {
            result.push_back("Impossible");
            return result;
        }
        int L = (dest_j - j_end) / 2;
        if (L >= 0)
        {
            oss << lls + L;
            result.push_back(oss.str());
            oss.str("");
            for (size_t i = 0; i < (size_t)lls; i++)
            {
                oss << "LL";
                if ((long)i != lls - 1)
                    oss << " ";
            }
            if (L)
                oss << " ";
            for (size_t i = 0; i < (size_t)L; i++)
            {
                oss << "L";
                if ((long)i < L - 1)
                    oss << " ";
            }
        }
        else
        { // L < 0
            oss << lls;
            result.push_back(oss.str());
            oss.str("");
            for (int i = L; i < 0; i++)
            {
                oss << "LR";
                if (i < -1)
                    oss << " ";
            }
            if (lls + L)
                oss << " ";
            for (size_t i = 0; i < (size_t)(lls + L); i++)
            {
                oss << "LL";
                if ((long)i != (lls + L - 1))
                    oss << " ";
            }
        }
    }
    // Lower Right
    else if (i_end > i_start && j_end > j_start)
    {
        if ((i_end - i_start) % 2)
        {
            result.push_back("Impossible");
            return result;
        }
        int lrs = (i_end - i_start) / 2;
        int dest_j = j_start + lrs;
        if ((abs(j_end - dest_j)) % 2)
        {
            result.push_back("Impossible");
            return result;
        }
        int R = (j_end - dest_j) / 2;
        if (R >= 0)
        {
            oss << lrs + R;
            result.push_back(oss.str());
            oss.str("");
            for (size_t i = 0; i < (size_t)R; i++)
            {
                oss << "R";
                if ((long)i < R - 1)
                    oss << " ";
            }
            if (lrs)
                oss << " ";
            for (size_t i = 0; i < (size_t)lrs; i++)
            {
                oss << "LR";
                if ((long)i != lrs - 1)
                    oss << " ";
            }
        }
        else
        { // R < 0
            oss << lrs;
            result.push_back(oss.str());
            oss.str("");
            for (size_t i = 0; i < (size_t)(lrs + R); i++)
            {
                oss << "LR";
                if (i != (lrs + R - 1))
                    oss << " ";
            }
            if (R < 0)
                oss << " ";
            for (int i = R; i < 0; i++)
            {
                oss << "LL";
                if (i < -1)
                    oss << " ";
            }
        }
    }
    // UP
    else if (j_end == j_start && i_end < i_start)
    {
        size_t diff = i_start - i_end;
        if (diff % 4)
        {
            result.push_back("Impossible");
            return result;
        }
        else
        {
            oss << diff / 2;
            result.push_back(oss.str());
            oss.str("");
            for (size_t i = 0; i < (diff / 4); i++)
            {
                oss << "UL UR";
                if (i != (diff / 4) - 1)
                    oss << " ";
            }
        }
    }
    // DOWN
    else if (j_end == j_start && i_end > i_start)
    {
        size_t diff = i_end - i_start;
        if (diff % 4)
        {
            result.push_back("Impossible");
            return result;
        }
        else
        {
            oss << diff / 2;
            result.push_back(oss.str());
            oss.str("");
            for (size_t i = 0; i < (diff / 4); i++)
            {
                oss << "LR LL";
                if (i != (diff / 4) - 1)
                    oss << " ";
            }
        }
    }
    // Left
    else if (i_end == i_start && j_end < j_start)
    {
        if ((j_start - j_end) % 2)
        {
            result.push_back("Impossible");
            return result;
        }
        size_t L = (j_start - j_end) / 2;
        oss << L;
        result.push_back(oss.str());
        oss.str("");
        for (size_t i = 0; i < L; i++)
        {
            oss << "L";
            if (i != L - 1)
                oss << " ";
        }
    }
    // Right
    else if (i_end == i_start && j_end > j_start)
    {
        if ((j_end - j_start) % 2)
        {
            result.push_back("Impossible");
            return result;
        }
        size_t R = (j_end - j_start) / 2;
        oss << R;
        result.push_back(oss.str());
        oss.str("");
        for (size_t i = 0; i < R; i++)
        {
            oss << "R";
            if (i != R - 1)
                oss << " ";
        }
    }
    else
    {
        // Destination = start?
        oss << 0 << endl;
    }
    result.push_back(oss.str());
    return result;
}
/*
 * https://leetcode.com/problems/koko-eating-bananas/
 * Find the minimum speed needed to consume all piles in the given hours.
 * Use binary search
 * 100%
 */
size_t Search::MinEatingSpeed(vector<size_t> const& piles, size_t hours)
{
    /*
    rate = n / duration
    duration = n / rate
    */
    size_t start = 1, mid = 0, end = *ranges::max_element(piles); // These are the rates of #bananas / hour. start = 0 will hit division-by-zero
    for (; start <= end;)
    {
        mid = start + (end - start) / 2 + (end - start) % 2; // If modulo component is added, mid - 1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        if (_CanEatAllBananasInTime(piles, mid, hours))
            end = mid - 1;
        else
            start = mid + 1;
    }
    return start; // start is the minimal k​ satisfying the condition function.
}
bool Search::_CanEatAllBananasInTime(vector<size_t> const& piles, size_t rate, size_t hours)
{
    size_t duration = parallel_reduce(
        blocked_range<size_t>(0, piles.size()), 0, [rate, &piles](tbb::blocked_range<size_t> const& r, size_t running_total)
        {
            for (size_t i = r.begin(); i < r.end(); i++)
                running_total += (size_t)(piles[i] / rate) + ((piles[i] % rate) ? 1 : 0);
            return running_total; },
        std::plus<size_t>());
    return duration <= hours;
}
bool Search::_IsValidSubSequence(vector<size_t> const& data, size_t check, size_t k)
{
    size_t count = 1, sum = 0;
    for (vector<size_t>::const_iterator it = data.begin(); it != data.end(); it++)
    {
        sum += *it;
        if (sum > check)
        {
            sum = *it;
            if (++count > k) // Too heavy. Ship the next day.
                return false;
        }
    }
    return true;
}
/*
 * https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
 * Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.
 * Use binary search
 * 100%
 */
size_t Search::MinCapacityToShipWithinDays(vector<size_t> const& weights, size_t days)
{
    /* Start with the weight of the single largest item. If start with min_element, other items with weights larger than it cannot fit into the capacity */
    size_t start = *ranges::max_element(weights), end = ranges::fold_left(weights, 0, std::plus<size_t>());
    for (; start <= end;)
    {
        int mid = start + (end - start) / 2 + (end - start) % 2; // If modulo component is added, mid -1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        /*
         * The following condition shows monotonicity. If condition(mid) is True, end = mid - 1. So condition is True for all values of (mid - 1)
         * If condition(mid) is true, condition(mid + 1) is True. This is prerequisite for applying binary search as a solution to the problem.
         */
        if (_IsValidSubSequence(weights, mid, days))
            end = mid - 1; // Return the least weight capacity of the ship. So, we decrease our capacity as long as it fits within days. Use mid instead of (mid - 1) because it needs to load the complete weight of the item
        else
            start = mid + 1; // If cannot ship within days, increase capacity.
    }
    return start; // start is the minimal k​ satisfying the condition function.
}
/*
 * https://leetcode.com/problems/split-array-largest-sum/description/
 * Return the minimized largest sum of the k-split subsequences.
 * Use binary search
 * 100%
 */
size_t Search::MinimumLargestSum(vector<size_t> const& data, size_t k)
{
    long start = *ranges::max_element(data), end = ranges::fold_left(data, 0, std::plus<long>());
    for (; start <= end;)
    {
        int mid = start + (end - start) / 2 + (end - start) % 2; // If modulo component is added, mid - 1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        /*
         * The following condition shows monotonicity. If condition(mid) is True, end = mid - 1. So condition is True for all values of (mid - 1)
         * If condition(mid) is true, condition(mid + 1) is True. This is prerequisite for applying binary search as a solution to the problem.
         */
        if (_IsValidSubSequence(data, mid, k))
            end = mid - 1; // Return the least weight capacity of the ship. So, we decrease our capacity as long as it fits within days. Use mid instead of (mid - 1) because it needs to load the complete weight of the item
        else
            start = mid + 1; // If cannot ship within days, increase capacity.
    }
    return start; // start is the minimal k​ satisfying the condition function.
}
bool Search::_CanMakeBouquets(vector<size_t> const& bloomDay, size_t m, size_t k, size_t day)
{
    string flowers = "";
    for (size_t i = 0; i < bloomDay.size(); i++)
        flowers.append(1, bloomDay[i] <= day ? 'f' : '-');
    size_t bouquets = 0, count = 0 /* count of consequtive flowers */;
    for (size_t i = 0; i < flowers.size(); i++)
    {
        if (flowers[i] == 'f')
            count++;
        else
            count = 0;
        if (count == k)
        {
            bouquets++;
            count = 0;
        }
        if (bouquets >= m)
            return true;
    }
    return false;
}
/*
 * https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/description/
You are given an integer array bloomDay, an integer m and an integer k.
You want to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.
The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] and then can be used in exactly one bouquet.
Return the minimum number of days you need to wait to be able to make m bouquets from the garden. If it is impossible to make m bouquets return -1.
 * Use binary search
 * 100%
 */
long Search::MinDaysToMakeBouquets(vector<size_t> const& bloomDays, size_t m, size_t k)
{
    if (bloomDays.size() < (uint64_t)((uint64_t)m * (uint64_t)k))
        return -1;
    size_t start = *ranges::min_element(bloomDays), end = *ranges::max_element(bloomDays);
    for (; start <= end;)
    {
        size_t mid = start + (end - start) / 2 + (end - start) % 2; // If modulo component is added, mid - 1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        /*
         * The following condition shows monotonicity. If condition(mid) is True, end = mid - 1. So condition is True for all values of (mid - 1)
         * If condition(mid) is true, condition(mid + 1) is True. This is prerequisite for applying binary search as a solution to the problem.
         */
        if (_CanMakeBouquets(bloomDays, m, k, mid))
            end = mid - 1;
        else
            start = mid + 1;
    }
    return start; // start is the minimal k​ satisfying the condition function.
}
bool Search::_HasKthSmallest(size_t m, size_t n, size_t k, size_t current)
{
    size_t count = 0;
    for (size_t i = 1; i <= m; i++)
    {
        /* Every number in a row is a multiple of the row#
         * Ex: row 3: [3	6	9	12	15]
         * To calculate the offset of current in a row, row * offset <= current,
         * offset = min(current / row, n)
         * "offset of current in a row" means if current is to be put into row i, which 1-based col does it fit into.
         */
        size_t offset = min(current / i, n);
        if (!offset)
            break;
        count += offset;
    }
    return count >= k;
}
/*
 * https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
 * return the kth smallest element in the m x n multiplication table.
 * Use binary search
 * 100%
1	2	3	4	5
2	4	6	8	10
3	6	9	12	15 <= In each row, the value += #row from left to right.
4	8	12	16	20
5	10	15	20	25

1 2 2 3 3 4 4 4 5 5 6 6 8 8 9 10 10 12 12 15 15 16 20 20 25

mid:25//2 = 13
      add: min(get the count of multiples of row#, max in the row=col)
row:1 add: min(13, 5)=5 count=5
row:2 add: min(13//2, 5)=min(6,5)=5 count=10
row:3 add: min(13//3, 5)=min(4,5)=4 count=14
row:4 add: min(13//4, 5)=min(3,5)=3 count=17
row:5 add: min(13//5, 5)=min(2,5)=2 count=19
 */
size_t Search::MultiplicationTableKthSmallestNumber(size_t m, size_t n, size_t k)
{
    size_t start = 1, end = m * n;
    for (; start <= end;)
    {
        size_t mid = start + (end - start) / 2 + (end - start) % 2; // If modulo component is added, mid - 1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        /*
         * The following condition shows monotonicity. If condition(mid) is True, end = mid - 1. So condition is True for all values of (mid - 1)
         * If condition(mid) is true, condition(mid + 1) is True. This is prerequisite for applying binary search as a solution to the problem.
         */
        if (_HasKthSmallest(m, n, k, mid))
            end = mid - 1;
        else
            start = mid + 1;
    }
    return start; // start is the minimal k​ satisfying the condition function.
}
bool Search::_HasKthSmallestPairs(vector<size_t>& data, size_t k, size_t distance)
{
    size_t pairs = 0;
    // The entire for loop is actually calculating Binomial Coefficients.
    for (size_t i = 0, j = 1; i < data.size() || j < data.size(); i++)
    {
        // If the current pair pointed at has a distance less than or equal to distance, all pairs between these pointers are valid (since the array is already sorted),
        for (; j < data.size() && abs((long)(data[j] - data[i])) <= (long)distance; j++)
            ;
        pairs += (j - i - 1);
    }
    return pairs >= k;
}
/*
 * https://leetcode.com/problems/find-k-th-smallest-pair-distance/
 * Use binary search
 * 100%
 *
--- size_t mid = start + (end - start) / 2 + (end - start) % 2; --- doesn't work
1 1 6 k:3 [1,1] [1,6] [1,6]
[start: 0, end: 5 mid: 3]
i:0, j:1, v:0 j:2
i:0, j:2, v:5 pairs = 2 - 0 - 1 = 1

i:1, j:2 v:5
i:2, j:2 v:0 j:3 pairs += 3 - 2 - 1 = 1 condition: false
BinomialCoefficients(2) = 2(1) / 2 = 1 condition: false

[start: 4, end: 5 mid:5]
i:0, j:1, v:0 j:2
i:0, j:2, v:5 j:3
pairs += 3 - 0 - 1 = 2

i:1, j:3 pairs += 3 - 1 - 1 = 2 + 1 = 3
i:2, j:3 pairs += 3 - 2 - 1 = 3 + 0 = 3 condition: true
BinomialCoefficients(3) = 3(2) / 2 = 3 condition: true

[start: 4, end: 4] => return 4
------ size_t mid = start + (end - start) / 2; --- works
1 1 6 k:3 [1,1] [1,6] [1,6]
[start: 0, end: 5 mid: 2]
i:0, j:1, v:0 j:2
i:0, j:2, v:5 pairs = 2 - 0 - 1 = 1

i:1, j:2 v:5
i:2, j:2 v:0 j:3 pairs += 3 - 2 - 1 = 1 condition: false
BinomialCoefficients(2) = 2(1) / 2 = 1 condition: false

[start: 3, end: 5 mid:4]
i:0, j:1, v:0 j:2
i:0, j:2, v:5 j:2
pairs += 2 - 0 - 1 = 1

i:1, j:2, v:5 pairs += 2 - 1 - 1 = 0 + 1 = 1
i:2, j:2, v:0, j:3 pairs += 3 - 2 - 1 = 0 + 1 = 1 condition: false
BinomialCoefficients(2) = 2(1) / 2 = 1 condition: false

[start: 4, end: 5, mid:4]
i:0, j:1, v:0 j:2
i:0, j:2, v:5 j:2
pairs += 2 - 0 - 1 = 1

i:1, j:2, v:5 pairs += 2 - 1 - 1 = 0 + 1 = 1
i:2, j:2, v:0, j:3 pairs += 3 - 2 - 1 = 0 + 1 = 1 condition: false
BinomialCoefficients(2) = 2(1) / 2 = 1 condition: false

[start: 5, end: 5, mid:4] => return 5
*/
int Search::SmallestDistancePair(vector<size_t>& data, size_t k)
{
    ranges::sort(data);
    size_t start = 0, end = data.back() - data.front();
    for (; start < end;)
    {
        // size_t mid = start + (end - start) / 2 + (end - start) % 2; // XXX: Doesn't work in this case. If modulo component is added, mid - 1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        size_t mid = start + (end - start) / 2;
        if (_HasKthSmallestPairs(data, k, mid))
            end = mid;
        else
            start = mid + 1;
    }
    return start;
}
bool Search::_HasNUglyNumbers(size_t n, uint64_t a, uint64_t b, uint64_t c, uint64_t check)
{
    return (check / a + check / b + check / c - check / _lcm_ab - check / _lcm_bc - check / _lcm_ac + check / _lcm_abc) >= n;
}
/*
 * https://leetcode.com/problems/ugly-number-iii/
 * An ugly number is a positive integer that is divisible by a, b, or c. Given four integers n, a, b, and c, return the nth ugly number.
 *
 * Use binary search
 * 100%
Generating ugly numbers one at a time is too slow. Instead, ask a simpler question: how many ugly numbers are ≤ x?
That count only goes up as x grows, so you binary search for the smallest x whose count is at least n. The result is guaranteed to fall in [1, 2 × 10⁹], which gives you the search range.
The number of multiples of a up to x is ⌊x/a⌋. Adding ⌊x/a⌋ + ⌊x/b⌋ + ⌊x/c⌋ overcounts numbers divisible by more than one of them, so you correct with inclusion–exclusion:

count(x) = x/a + x/b + x/c − x/lcm(a,b) − x/lcm(a,c) − x/lcm(b,c) + x/lcm(a,b,c)

A number divisible by both a and b is a multiple of lcm(a, b), not of a·b. Those are the same only when a and b share no factors. Example 2 shows why this matters: with a = 2 and c = 4, every multiple of 4 is already a multiple of 2, so the overlap is “multiples of 4”, not “multiples of 8”. Using a·b would subtract the wrong amount and give a wrong answer.

The standard way to get the LCM is through the GCD:

lcm(a, b) = a / gcd(a, b) × b

and lcm(a, b, c) = lcm(lcm(a, b), c). GCD itself is cheap to compute with Euclid’s algorithm in O(log min(a, b)) time.

Two practical notes:
1. Divide before multiplying (a / gcd(a,b) * b) to reduce overflow risk, and use 64-bit integers. The constraint a × b × c ≤ 10¹⁸ guarantees even the three-way LCM fits in a 64-bit integer.
2. If an LCM exceeds 2 × 10⁹, its term is simply 0 for every x in range, which is fine.

The addition term of x/lcm(a,b,c) is there because the pairwise subtractions remove numbers divisible by all three one time too many. Follow a single such number through the formula.

Take a = 2, b = 3, c = 5, and look at the number 30, which is divisible by all three.

Step 1: the single terms (x/a + x/b + x/c)
30 is a multiple of 2, of 3 and of 5, so it gets counted 3 times.

Step 2: subtract the pairwise overlaps (− x/lcm(a,b) − x/lcm(a,c) − x/lcm(b,c))
30 is a multiple of lcm(2,3)=6, of lcm(2,5)=10 and of lcm(3,5)=15, so it gets subtracted 3 times.

Running total for 30: 3 − 3 = 0. It has disappeared from the count, even though it’s an ugly number and should count exactly once.

Step 3: add back the triple overlap (+ x/lcm(a,b,c))
30 is a multiple of lcm(2,3,5)=30, so it’s added once. Total: 1. Correct.

Compare with a number like 6, divisible by 2 and 3 but not 5: it’s counted twice in step 1, subtracted once in step 2 (only by the 6 term), and not touched in step 3. Total 2 − 1 = 1. Fine without any correction.

So the rule is:

Number divisible by…	Step 1	Step 2	Step 3	Total
exactly one of a, b, c	+1	    0	    0	    1
exactly two	            +2	    −1	    0	    1
all three	            +3	    −3	    +1	    1

If you picture the three overlapping circles of a Venn diagram, the centre region sits inside every pairwise overlap, so subtracting all three overlaps cuts it out three times after it was only added three times. The final term puts it back.

#multiples of a up to x = x / a
x:10
a:2
b:4

divisable by both a and b: 2 4 6 8 10

x/a = 5
x/b = 2

x/a + x/b = 7 <- overcount by 2
 */
size_t Search::NthUglyNumber(size_t n, size_t a, size_t b, size_t c)
{
    size_t start = 1, end = 2 * pow(10, 9);
    _lcm_ab = (uint64_t)(a * b) / gcd(a, b);
    _lcm_bc = (uint64_t)((uint64_t)b * (uint64_t)c) / gcd(b, c);
    _lcm_ac = (uint64_t)(a * c) / gcd(a, c);
    _lcm_abc = (uint64_t)(_lcm_ab * c) / gcd(_lcm_ab, c);
    for (; start < end;)
    {
        // size_t mid = start + (end - start) / 2 + (end - start) % 2; // XXX: Doesn't work in this case. If modulo component is added, mid - 1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        size_t mid = start + (end - start) / 2;
        if (_HasNUglyNumbers(n, a, b, c, mid))
            end = mid;
        else
            start = mid + 1;
    }
    return start;
}
bool Search::_WithinThreshold(vector<size_t> const& data, size_t threshold, size_t check)
{
#if 0
    This also works!
        size_t result = ranges::fold_left(data | std::views::transform([&](size_t x) { return ceil_div(x, check); }), 0, std::plus<size_t>()) <= threshold;
#endif
    size_t result = parallel_reduce(
        blocked_range<size_t>(0, data.size()), 0, [check, &data](tbb::blocked_range<size_t> const& r, size_t running_total)
        {
            for (size_t i = r.begin(); i < r.end(); i++)
                running_total += ceil_div(data[i], check);
            return running_total; },
        std::plus<size_t>());
    return result <= threshold;
}
/*
 * https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/description/
 * Use binary search
 * 100%
 */
size_t Search::SmallestDivisor(vector<size_t> const& data, size_t threshold)
{
    size_t start = 1, end = *ranges::max_element(data);
    for (; start < end;)
    {
        // size_t mid = start + (end - start) / 2 + (end - start) % 2; // XXX: Doesn't work in this case. If modulo component is added, mid - 1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        size_t mid = start + (end - start) / 2;
        if (_WithinThreshold(data, threshold, mid))
            end = mid;
        else
            start = mid + 1;
    }
    return start;
}
/*
The key fact: the cost of one substring
Match brackets greedily from left to right, as in the usual stack check. Whatever stays unmatched always looks like )))…(((: a unmatched ) followed by b unmatched (. The fewest flips that make the substring valid is then:
⌈a/2⌉ + ⌈b/2⌉ (and the length must be even)
You flip half of the )s to ( and half of the (s to ). For example, "))))" needs 2 flips, giving "()()".
If a is odd, b is odd too, because the length is even, and the middle ")(" costs 2.
So the task becomes: find the longest even-length substring with ⌈a/2⌉ + ⌈b/2⌉ ≤ K.
x:       0  1  2  (k = 2)
bracket:  )  (
P[x]     0 -1  0
t: 1, m = -1, a = P[0] - m = 0 - -1 = 1 startCost = 1, remainingFlips = k - 1 = 1
              b = 1 * 2 = 2 -> 1 (If a is odd, b is odd too, because the length is even)
     result: str[0,1]
*/
size_t Search::_BinarySearchLongestValidParenthesesWithFixes(size_t k, vector<long> const& P, long start, long end)
{
    size_t result = 0;
    if (start >= end)
        return 0;
    vector<long>::const_iterator lowestIt = min_element(P.begin() + start, P.begin() + end + 1);
    if (lowestIt != P.begin() + end + 1) {
        size_t t = distance(P.begin() + start, lowestIt);
        long m = *lowestIt;
        size_t leftSize = t - start, rightSize = end - t;
        // Loop over the smaller side
        if (leftSize <= rightSize)
            for (size_t i = start; i < t; i++) {
                long a = P[i] - m;
                long startCost = a / 2 + a % 2, remainingFlips = k - startCost;
                long j = end;
                if (remainingFlips > 0) {
                    // b / 2 + b % 2 = remainingFlips
                    long b = 2 * remainingFlips; // b <= 2 * remainingFlips
                    // If a is odd, b is odd too, because the length is even
                    b -= ((a % 2) != (b % 2)) && b > 0 ? 1 : 0;
                    /*
                    The “allowed P at the other end”:
                    b = P[j] − m <= 2 * remainingFlips
                    P[i] - m <= 2 * remainingFlips
                    P[i] <= 2 * remainingFlips + m
                    */
                    long allowedP = b + m;
                    for (; j > start && P[j] != allowedP; j--);
                }
                result = max<size_t>(result, j - i + 1);
            }
        else
            for (size_t j = t + 1; j <= end; j++) {
                long b = P[j] - m;
                long startCost = b / 2 + b % 2, remainingFlips = k - startCost;
                size_t i = start;
                if (remainingFlips > 0) {
                    // a / 2 + a % 2 = remainingFlips
                    long a = 2 * remainingFlips; // b <= 2 * remainingFlips
                    // If a is odd, b is odd too, because the length is even
                    a -= ((a % 2) != (b % 2)) && a > 0 ? 1 : 0;
                    /*
                    The “allowed P at the other end”:
                    b = P[j] − m <= 2 * remainingFlips
                    P[i] - m <= 2 * remainingFlips
                    P[i] <= 2 * remainingFlips + m
                    */
                    long allowedP = a + m;
                    for (; i < t && P[i] != allowedP; i++);
                }
                result = max<size_t>(result, j - i + 1);
            }
        result = max<size_t>(result, max<size_t>(_BinarySearchLongestValidParenthesesWithFixes(k, P, start, t - 1), _BinarySearchLongestValidParenthesesWithFixes(k, P, t + 1, end)));
    }
    return result;
}
/* https://app.codility.com/programmers/task/brackets_rotation/
 * Divide and conquer on the minimum prefix balance.
The divide and conquer works on prefix balances, P[x] = (number of () − (number of )) in the first x brackets. For a substring from i to j, with m the minimum of P between them, a = P[i] − m and b = P[j] − m.

1. Take t, the position of the minimum P in the current range. Every substring passing through t has m = P[t].
2. For each index on the smaller side of t, the formula gives the largest P allowed at the other end. A sparse table then finds the farthest index on the other side, of the same parity, with P that small. Each lookup is a binary search, O(log N).
3. Recurse on the two sides.

Iterating the smaller side keeps the total to O(N log N) lookups, the same reasoning as “small-to-large” merging. That’s where O(N log² N) comes from.

Think of P as a path going up and down. For the substring s[i..j), look at the part of the path from position i to position j:

m is the lowest point on that part of the path.
a = P[i] − m is how far the path drops below where it started. Each drop below the starting level is a ) with no ( before it to match: an unmatched ).
b = P[j] − m is how far the path ends above its lowest point. Each step up after the lowest point that never comes back down is a ( with no ) after it: an unmatched (.

Example: s[0..6) = )(())(. The path is P[0..6] = 0, −1, 0, 1, 0, −1, 0.

It starts at 0, the lowest point is m = −1, and it ends at 0.
a = 0 − (−1) = 1: the first ) has nothing to match.
b = 0 − (−1) = 1: the last ( has nothing to match.
Cost = ⌈1/2⌉ + ⌈1/2⌉ = 2 flips, giving ((())). With K = 1, that’s too many.

A second example: s[1..5) = (()). The path is −1, 0, 1, 0, −1, so m = −1, and a = 0, b = 0. It’s already valid and costs 0.

The divide and conquer, step by step:

Point 1: split at the lowest point of the whole range. Over all positions 0 … 7, the lowest P is −1. It first occurs at t = 1. Every substring s[i..j) that contains position t (i ≤ 1 ≤ j) passes through that lowest point, so its m is −1. That means its m is known without any searching. Substrings that don’t contain t lie entirely to the left of t or entirely to the right, and point 3 deals with those.

Point 2: for each start, find the farthest end that’s affordable. Take i = 1 (on the left of t, or at t itself):

a = P[1] − m = −1 − (−1) = 0, so the start costs ⌈0/2⌉ = 0 flips.
That leaves K − 0 = 1 flip for the b side, so b ≤ 2, since ⌈2/2⌉ = 1.
b = P[j] − m, so P[j] ≤ m + 2 = 1. That’s the “allowed P at the other end”.
The length j − i must be even. So j must have the same parity as i: both odd here.
On the right of t, the farthest odd position with P ≤ 1 is j = 7 (P[7] = 1). So s[1..7) = (())((, length 6. Its b is 2, costing 1 flip ✓.
Now take i = 0: a = 0 − (−1) = 1, which costs ⌈1/2⌉ = 1 flip. That uses the whole budget, leaving 0 flips for the b side. Since a is odd, b is also odd (the length is even), so b ≥ 1 and costs at least 1 more flip. That’s impossible, so no j works for i = 0.
You always want the farthest valid end, because we’re looking for the longest substring. Finding it is where the sparse table comes in. It’s a lookup structure that answers “what’s the last position in this range with this parity and P ≤ some value?” with a binary search, instead of scanning every position.
Which side to loop over. Here the left side of t has 2 positions (0, 1) and the right side has 7 (1 … 7). Looping over the smaller side and doing a lookup on the bigger side keeps the total work down. That choice is what makes it O(N log² N) instead of O(N²). The result is the same whichever side you loop over.

Point 3: repeat on each side. Substrings that don’t contain t = 1 lie entirely within positions 0 … 0, which is too short, or entirely within positions 2 … 7. So the same steps run on 2 … 7: its lowest point is t = 5 (P = −1), and the search finds )) and (( (length 2 each). It then splits again, into 2 … 4 and 6 … 7, and so on, until the ranges are too short to hold a substring.

The full trace finds 6 as the longest, which matches the brute force:

Range of positions	Lowest point t	Best substring found through t
0 … 7	1 (P = −1)	s[1..7) = (())((, length 6
2 … 7	5 (P = −1)	)) or ((, length 2
2 … 4	2 (P = 0)	(), length 2
6 … 7, 3 … 4	6, 4	nothing longer

Every substring is checked exactly once: in the first range that contains it whose split point t falls inside it. At that point t is its lowest point, so its m is P[t].

WIP: Using recursive algorithm hits stack overflow.
 */
size_t Search::LongestValidParenthesesWithFixes(string const& str, size_t k)
{
    if (str.empty())
        return 0;
    if (k >= str.size() - str.size() % 2)
        return str.size() - str.size() % 2;
    vector<long> P(str.size() + 1, 0);
    for (size_t i = 0; i < str.size(); i++)
        P[i + 1] = (str[i] == ')' ? P[i] - 1 : P[i] + 1);
    return _BinarySearchLongestValidParenthesesWithFixes(k, P, 0, P.size() - 1);
}