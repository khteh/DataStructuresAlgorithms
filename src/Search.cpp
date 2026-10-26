#include "pch.h"
#include "Search.h"
/* https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 * https://cp-algorithms.com/string/prefix-function.html
 */
void Search::KMPTable(string const &w, vector<long> &T)
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
void Search::KMPSearch(string const &s, string const &w, vector<size_t> &result)
{
    vector<long> T;
    KMPTable(w, T);
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
vector<long> Search::SearchRange(size_t target, vector<size_t> const &nums)
{
    long start = 0, end = nums.size() - 1, middle = end / 2 + end % 2;
    vector<long> result{-1, -1}; // result[0] = start (inclusive); result[1] = end (exclusive)
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
long Search::BinarySearch(size_t toSearch, vector<size_t> const &data)
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
long Search::BinarySearchMinimum(vector<long> const &data, long start, long end)
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
int Search::BinarySearchCountUpper(vector<long> const &source, long toSearch, long start, long end)
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
int Search::BinarySearchCountLower(vector<long> const &source, long toSearch, long start, long end)
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
int Search::BinarySearch(const string &toSearch, vector<string> const &source)
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
bool Search::GridSearch(vector<string> const &pattern, vector<string> const &grid)
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
            locations = locations1;
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
                locations = intersections;
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
size_t Search::MinEatingSpeed(vector<size_t> const &piles, size_t hours)
{
    /*
    rate = n / duration
    duration = n / rate
    */
    size_t start = 1, mid = 0, end = *ranges::max_element(piles); // These are the rates of #bananas / hour. start = 0 will hit division-by-zero
    for (; start <= end;)
    {
        mid = start + (end - start) / 2 + (end - start) % 2; // If modulo component is added, mid -1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        if (CanEatAllBananasInTime(piles, mid, hours))
            end = mid - 1;
        else
            start = mid + 1;
    }
    return start;
}
bool Search::CanEatAllBananasInTime(vector<size_t> const &piles, size_t rate, size_t hours)
{
    size_t duration = parallel_reduce(
        blocked_range<size_t>(0, piles.size()), 0, [rate, &piles](tbb::blocked_range<size_t> const &r, size_t running_total)
        {
            for (size_t i = r.begin(); i < r.end(); i++)
                running_total += (size_t)(piles[i] / rate) + ((piles[i] % rate) ? 1 : 0); 
            return running_total; },
        std::plus<size_t>());
    return duration <= hours;
}
/*
 * https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
 * Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.
 * Use binary search
 * 100%
 */
size_t Search::MinCapacityToShipWithinDays(vector<size_t> const &weights, size_t days)
{
    /* Start with the weight of the single largest item. If start with min_element, other items with weights larger than it cannot fit into the capacity */
    size_t start = *ranges::max_element(weights), end = ranges::fold_left(weights, 0, std::plus<size_t>());
    for (; start <= end;)
    {
        int mid = start + (end - start) / 2 + (end - start) % 2; // If modulo component is added, mid -1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        if (IsValidSubSequence(weights, mid, days))
            end = mid - 1; // Return the least weight capacity of the ship. So, we decrease our capacity as long as it fits within days. Use mid instead of (mid - 1) because it needs to load the complete weight of the item
        else
            start = mid + 1; // If cannot ship within days, increase capacity.
    }
    return start;
}
bool Search::IsValidSubSequence(vector<size_t> const &data, size_t check, size_t k)
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
 * https://leetcode.com/problems/split-array-largest-sum/description/
 * Return the minimized largest sum of the k-split subsequences.
 * Use binary search
 * 100%
 */
size_t Search::MinimumLargestSum(vector<size_t> const &data, size_t k)
{
    long start = *ranges::max_element(data), end = ranges::fold_left(data, 0, std::plus<long>());
    for (; start <= end;)
    {
        int mid = start + (end - start) / 2 + (end - start) % 2; // If modulo component is added, mid -1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        if (IsValidSubSequence(data, mid, k))
            end = mid - 1; // Return the least weight capacity of the ship. So, we decrease our capacity as long as it fits within days. Use mid instead of (mid - 1) because it needs to load the complete weight of the item
        else
            start = mid + 1; // If cannot ship within days, increase capacity.
    }
    return start;
}
bool Search::CanMakeBouquets(vector<size_t> const &bloomDay, size_t m, size_t k, size_t day)
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
long Search::MinDaysToMakeBouquets(vector<size_t> const &bloomDays, size_t m, size_t k)
{
    if (bloomDays.size() < (uint64_t)((uint64_t)m * (uint64_t)k))
        return -1;
    size_t start = *ranges::min_element(bloomDays), end = *ranges::max_element(bloomDays);
    for (; start <= end;)
    {
        size_t mid = start + (end - start) / 2 + (end - start) % 2; // If modulo component is added, mid -1 and mid + 1 should always be used. Otherwise will hit infinite loop for any (end - start) == 1
        if (CanMakeBouquets(bloomDays, m, k, mid))
            end = mid - 1;
        else
            start = mid + 1;
    }
    return start;
}