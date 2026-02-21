/*
 * Heaters
 *
 *  Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.
 *
 *  Every house can be warmed, as long as the house is within the heater's warm radius range. 
 *
 *  Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.
 *
 *  Notice that all the heaters follow your radius standard, and the warm radius will the same.
 *
 *  Constraints:
 *  1 <= houses.length, heaters.length <= 3 * 104
 *  1 <= houses[i], heaters[i] <= 109
 *  houses and heaters are sorted in non-decreasing order.
 * 
 *  Example 1:
 *  Input: houses = [1,2,3], heaters = [2]
 *  Output: 1
 *  Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
 *  Example 2:
 *  Input: houses = [1,2,3,4], heaters = [1,4]
 *  Output: 1
 *  Explanation: The two heaters were placed in the positions 1 and 4. We need to use a radius 1 standard, then all the houses can be warmed.
 *  Example 3:
 *  Input: houses = [1,5], heaters = [2]
 *  Output: 3
 * 
 */
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        // 排序方便双指针比较
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int i = 0, j = 0;
        int ans = 0;
        while (i < houses.size()) {
            // 如果当前加热器不是离houses[i]最近的，就移动j
            while (j + 1 < heaters.size() && 
                   abs(heaters[j + 1] - houses[i]) <= abs(heaters[j] - houses[i])) {
                ++j;
            }
            // 更新所需的最大半径
            ans = max(ans, abs(heaters[j] - houses[i]));
            ++i;
        }
        return ans;
    }
};