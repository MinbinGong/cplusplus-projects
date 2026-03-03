/**
 * 1482. Minimum Number of Days to Make m Bouquets
 * 
 * Given an integer array bloomDay, an integer m and an integer k.
 * 
 * We need to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.
 * 
 * The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] and then can be used in exactly one bouquet.
 * 
 * Return the minimum number of days you need to wait to be able to make m bouquets from the garden. If it is impossible to make m bouquets return -1.
 * 
 * Example 1:
 * 
 * Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
 * Output: 3
 * Explanation: Let's see what happened in the first three days. x means flower bloomed and _ means flower didn't bloom in the garden.
 * We need 3 bouquets each should contain 1 flower.
 * After day 1: [x, _, _, _, _]   // we can only make one bouquet.
 * After day 2: [x, _, _, _, x]   // we can only make two bouquets.
 * After day 3: [x, _, x, _, x]   // we can make 3 bouquets. The answer is 3.
 * 
 * Example 2:
 * 
 * Input: bloomDay = [1,10,3,10,2], m = 3, k = 2
 * Output: -1
 * Explanation: We need 3 bouquets each has 2 flowers, that means we need 6 flowers. We only have 5 flowers so it is impossible to get the needed bouquets and we return -1.
 * 
 * Example 3:
 * 
 * Input: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
 * Output: 12
 * Explanation: We need 2 bouquets each should have 3 flowers.
 * Here's the garden after the 7 and 12 days:
 * After day 7: [x, x, x, x, _, x, x]
 * We can make one bouquet of the first three flowers that bloomed. We cannot make another bouquet from the last three flowers that bloomed because they are not adjacent.
 * After day 12: [x, x, x, x, x, x, x]
 * We can make two bouquets from the middle flowers. That is 2 bouquets in total.
 * 
 * Constraints:
 * 1 <= bloomDay.length <= 10^5
 * 1 <= bloomDay[i] <= 10^9
 * 1 <= m <= 10^6
 * 1 <= k <= bloomDay.length
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        // 如果需要的花朵总数超过总花朵数，不可能完成任务
        if (m > n / k) return -1;

        int left = 1, right = *max_element(bloomDay.begin(), bloomDay.end());
        int ans = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int bouquets = 0, consecutive = 0;
            for (int i = 0; i < n; ++i) {
                if (bloomDay[i] <= mid) {
                    consecutive++;
                    if (consecutive == k) {
                        bouquets++;
                        consecutive = 0;
                    }
                } else {
                    consecutive = 0;
                }
            }
            if (bouquets >= m) {
                ans = mid;
                right = mid - 1;  // 尝试寻找更小的天数
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
};