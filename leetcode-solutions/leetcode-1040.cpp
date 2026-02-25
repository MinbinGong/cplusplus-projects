/*
 * 1040. Moving Stones Until Consecutive II
 *
 * On an infinite number line, the position of the i-th stone is given by stones[i].
 * Call a stone an endpoint stone if it has the smallest or largest position.
 * 
 * Example 1:
 * Input: [7,4,9]
 * Output: 1
 * Explanation: 
 * We can move 4 -> 8 for one move, and then 9 -> 7 for two moves.
 * Or, we can move 9 -> 8 for two moves, and then 4 -> 7 for one move.
 * 
 * Example 2:
 * Input: [6,5,4,3,10]
 * Output: 2
 * Explanation: 
 * We can move 3 -> 8, then 4 -> 7, and 10 -> 9.
 * 
 * Note:
 * 1. 3 <= stones.length <= 10^4
 * 2. 1 <= stones[i] <= 10^9
 * 3. stones[i] have distinct values.
 * 4. The number of moves we would need to move a stone to an endpoint stone is <= 10^9.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        sort(stones.begin(), stones.end());
        int n = stones.size();
        
        // 计算最大移动次数
        int maxMoves = max(stones[n-1] - stones[1], stones[n-2] - stones[0]) - (n - 2);
        
        // 计算最小移动次数
        int minMoves = n;
        int j = 0;
        
        for (int i = 0; i < n; i++) {
            // 找到满足 stones[i] - stones[j] + 1 <= n 的最大j
            while (j + 1 < n && stones[j + 1] - stones[i] + 1 <= n) {
                j++;
            }
            
            int alreadyInWindow = j - i + 1;
            
            // 特殊情况：如果窗口内有n-1个连续石头，且空位在端点
            if (alreadyInWindow == n - 1 && stones[j] - stones[i] + 1 == n - 1) {
                minMoves = min(minMoves, 2);
            } else {
                minMoves = min(minMoves, n - alreadyInWindow);
            }
        }
        
        return {minMoves, maxMoves};
    }
};