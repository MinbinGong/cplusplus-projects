/**
 * 1471. The k Strongest Values in an Array
 * 
 * Given an array of integers arr and an integer k.
 * 
 * A value arr[i] is said to be stronger than a value arr[j] if |arr[i] - m| > |arr[j] - m| where m is the median of the array.
 * 
 * If |arr[i] - m| == |arr[j] - m|, then arr[i] is said to be stronger than arr[j] if arr[i] > arr[j].
 * 
 * Return a list of the strongest k values in the array. return the answer in any arbitrary order.
 * 
 * Median is the middle value in an ordered integer list. More formally, if the length of the list is n, the median is the element in position ((n - 1) / 2) in the sorted list (0-indexed).
 * 
 * Example 1:
 * 
 * Input: arr = [1,2,3,4,5], k = 2
 * Output: [5,1]
 * Explanation: Median is 3, the elements of the array sorted by the strongest are [5,1,4,2,3]. The strongest 2 elements are [5, 1]. [1, 5] is also accepted answer.
 * Please note that although |5 - 3| == |1 - 3| but 5 is stronger than 1 because 5 > 1.
 * 
 * Example 2:
 * 
 * Input: arr = [1,1,2,2,3], k = 2
 * Output: [2,3]
 * Explanation: Median is 2, the elements of the array sorted by the strongest are [3,2,1,1,2]. The strongest 2 elements are [2, 3]. [3, 2] is also accepted answer.
 * Please note that although |2 - 2| == |3 - 2| but 2 is stronger than 3 because 2 > 3.
 * 
 * Example 3:
 * 
 * Input: arr = [6,7,11,7,6,8], k = 5
 * Output: [11,8,6,6,7]
 * Explanation: Median is 7, the elements of the array sorted by the strongest are [11,8,6,6,7,7].
 * Any permutation of [11,8,6,6,7] is accepted.
 * 
 * Note:
 * 1 <= n <= 500
 * arr.length == 2n
 * 1 <= arr[i] <= 10^3
 * 1 <= k <= n
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        int median = arr[(n - 1) / 2];

        vector<int> result;
        int left = 0, right = n - 1;
        while (result.size() < k) {
            int diffLeft = abs(arr[left] - median);
            int diffRight = abs(arr[right] - median);
            if (diffLeft > diffRight) {
                result.push_back(arr[left++]);
            } else if (diffRight > diffLeft) {
                result.push_back(arr[right--]);
            } else {
                // equal diff, pick the larger value (arr[right] since array is sorted)
                result.push_back(arr[right--]);
            }
        }
        return result;
    }
};