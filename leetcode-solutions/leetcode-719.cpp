/*
 * K-th Smallest Pair Distance
 *
 * Given an integer array, return the k-th smallest distance among all the pairs. The distance of a pair (A, B) is defined as the absolute difference between A and B.
 * 
 * Example 1:
 * 
 * Input: nums = [1,3,1], k = 1
 * Output: 0 
 * Explanation:
 * Here are all the pairs:
 * (1,3) -> 2
 * (1,1) -> 0
 * (3,1) -> 2
 * Then the 1st smallest distance pair is (1,1), and its distance is 0.
 * 
 * Note:
 * 
 * 2 <= len(nums) <= 10000.
 * 0 <= nums[i] < 1000000.
 * 1 <= k <= len(nums) * (len(nums) - 1) / 2.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int low = 0;
        int high = nums.back() - nums.front();

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (countPairs(nums, mid) < k) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }

private:
    // Count number of pairs with distance <= target
    int countPairs(const vector<int>& nums, int target) {
        int n = nums.size();
        int count = 0;
        int j = 0;
        for (int i = 0; i < n; ++i) {
            // Expand j until nums[j] - nums[i] > target
            while (j < n && nums[j] - nums[i] <= target) {
                ++j;
            }
            count += j - i - 1;
        }
        return count;
    }
};