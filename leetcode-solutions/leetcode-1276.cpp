/**
 * 1276. Number of Burgers with No Waste of Ingredients
 * 
 * Given two integers tomatoSlices and cheeseSlices. The ingredients of different burgers are as follows:
 * 
 * Jumbo Burger: 4 tomato slices and 1 cheese slice.
 * Small Burger: 2 Tomato slices and 1 cheese slice.
 * Return [total_jumbo, total_small] so that the number of remaining tomatoSlices equal to 0 and the number of remaining cheeseSlices equal to 0. If it is not possible to make the remaining tomatoSlices and cheeseSlices equal to 0 return [].
 * 
 * Example 1:
 * Input: tomatoSlices = 16, cheeseSlices = 7
 * Output: [1,6]
 * Explanation: To make one jumbo burger and 6 small burgers we need 4*1 + 2*6 = 16 tomato and 1 + 6 = 7 cheese. There will be no remaining ingredients.
 * 
 * Example 2:
 * Input: tomatoSlices = 17, cheeseSlices = 4
 * Output: []
 * Explanation: There will be no way to use all ingredients to make small and jumbo burgers.
 * 
 * Example 3:
 * Input: tomatoSlices = 4, cheeseSlices = 17
 * Output: []
 * Explanation: Making 1 jumbo burger there will be 16 cheese remaining and making 2 small burgers there will be 15 cheese remaining.
 * 
 * Example 4:
 * Input: tomatoSlices = 0, cheeseSlices = 0
 * Output: [0,0]
 * 
 * Example 5:
 * Input: tomatoSlices = 2, cheeseSlices = 1
 * Output: [0,1]
 * 
 * Note:
 * 0 <= tomatoSlices <= 10^7
 * 0 <= cheeseSlices <= 10^7
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {
        // 设巨无霸数量为 j，小皇堡数量为 s
        // 则有：4j + 2s = tomatoSlices, j + s = cheeseSlices
        // 解得：j = (tomatoSlices - 2*cheeseSlices) / 2
        int diff = tomatoSlices - 2 * cheeseSlices;
        if (diff < 0 || diff % 2 != 0) return {};   // 不能为负且必须是偶数
        int jumbo = diff / 2;
        int small = cheeseSlices - jumbo;
        if (small < 0) return {};                   // 小皇堡数量不能为负
        return {jumbo, small};
    }
};