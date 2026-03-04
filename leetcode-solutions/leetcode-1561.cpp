/**
 * 1561. Maximum Number of Coins You Can Get
 * 
 * There are 3n piles of coins of varying size, you and your friends will take piles of coins as follows:
 * 
 * In each step, you will choose any 3 piles of coins (not necessarily consecutive).
 * Of your choice, Alice will pick the pile with the maximum number of coins.
 * You will pick the next pile with the maximum number of coins.
 * Your friend Bob will pick the last pile.
 * Repeat until there are no more piles of coins.
 * Given an array of integers piles where piles[i] is the number of coins in the ith pile.
 * 
 * Return the maximum number of coins that you can have.
 * 
 * Example 1:
 * Input: piles = [2,4,1,2,7,8]
 * Output: 9
 * Explanation: Choose the triplet (2, 7, 8), Alice Pick the pile with 8 coins, you the pile with 7 coins and Bob the last one.
 * 
 * Example 2:
 * Input: piles = [2,4,5]
 * Output: 4
 * Explanation: Choose the triplet (2, 4, 5), Alice Pick the pile with 5 coins, you the pile with 4 coins and Bob the last one.
 * 
 * Example 3:
 * Input: piles = [9,8,7,6,5,1,2,3,4]
 * Output: 18
 * Explanation: Choose the triplet (9, 7, 6), Alice Pick the pile with 9 coins, you the pile with 7 coins and Bob the last one.
 * 
 * Constraints:
 * 3 <= piles.length <= 10^5
 * piles.length % 3 == 0
 * 1 <= piles[i] <= 10^4
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& piles) {
        // 将堆按硬币数从小到大排序
        sort(piles.begin(), piles.end());
        int n = piles.size() / 3;  // 每个人能拿到的堆数
        int ans = 0;
        // 从第 n 个索引开始（0-based），每隔一个取一个，共取 n 个
        for (int i = n; i < piles.size(); i += 2) {
            ans += piles[i];
        }
        return ans;
    }
};