/**
 * Longest Well-Performing Interval
 * 
 * We are given hours, a list of the number of hours worked per day for a given employee.
 * 
 * A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.
 * 
 * A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.
 * 
 * Return the length of the longest well-performing interval.
 * 
 * 1 <= hours.length <= 10000
 * 0 <= hours[i] <= 16
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        int sum = 0, ans = 0;
        unordered_map<int, int> first;   // first occurrence of each prefix sum
        first[0] = -1;                    // base case: before the array

        for (int i = 0; i < n; ++i) {
            sum += (hours[i] > 8) ? 1 : -1;

            if (sum > 0) {
                // whole prefix [0..i] is valid
                ans = i + 1;
            } else {
                // sum <= 0: need a previous prefix sum < current sum
                // Because each step changes by ±1, the earliest such prefix
                // must have sum = sum - 1 (if it exists).
                if (first.count(sum - 1)) {
                    ans = max(ans, i - first[sum - 1]);
                }
                // Store first occurrence of current sum
                if (!first.count(sum)) {
                    first[sum] = i;
                }
            }
        }
        return ans;
    }
};