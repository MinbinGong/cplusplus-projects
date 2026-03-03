/**
 * 1481. Least Number of Unique Integers after K Removals
 * 
 * Given an array of integers arr and an integer k. Find the least number of unique integers after removing exactly k elements.
 * 
 * Example 1:
 * 
 * Input: arr = [5,5,4], k = 1
 * Output: 1
 * Explanation: Remove the single 4, only 5 is left.
 * 
 * Example 2:
 * 
 * Input: arr = [4,3,1,1,3,3,2], k = 3
 * Output: 2
 * Explanation: Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3 will be left.
 * 
 * Constraints:
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 10^9
 * 0 <= k <= arr.length
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        unordered_map<int, int> freq;
        for (int num : arr) {
            freq[num]++;
        }

        vector<int> counts;
        for (auto& p : freq) {
            counts.push_back(p.second);
        }
        sort(counts.begin(), counts.end());

        int unique = counts.size();
        for (int cnt : counts) {
            if (k >= cnt) {
                k -= cnt;
                unique--;
            } else {
                break;
            }
        }
        return unique;
    }
};