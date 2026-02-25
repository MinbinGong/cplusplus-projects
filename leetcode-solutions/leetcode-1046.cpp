/*
 * 1046. Last Stone Weight
 *
 * We have a collection of rocks, each rock has a positive integer weight.
 * 
 * Each turn, we choose the two heaviest rocks and smash them together.  Suppose the stones have weights x and y with x <= y.  The result of this smash is:
 * 
 * If x == y, both stones are totally destroyed;
 * If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
 * 
 * At the end, there is at most 1 stone left.  Return the weight of this stone (or 0 if there are no stones left.)
 * 
 * Example 1:
 * Input: [2,7,4,1,8,1]
 * Output: 1
 * Explanation: 
 * We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
 * we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
 * we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
 * we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of last stone.
 * 
 * Note:
 * 1. 1 <= stones.length <= 30
 * 2. 1 <= stones[i] <= 1000
 * 
 */
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        // 创建最大堆（优先队列默认是最大堆）
        priority_queue<int> maxHeap;
        
        // 将所有石头重量加入堆中
        for (int weight : stones) {
            maxHeap.push(weight);
        }
        
        // 当堆中还有至少两块石头时，继续处理
        while (maxHeap.size() > 1) {
            // 取出最重的两块石头
            int stone1 = maxHeap.top();
            maxHeap.pop();
            int stone2 = maxHeap.top();
            maxHeap.pop();
            
            // 计算碰撞后的结果
            if (stone1 != stone2) {
                maxHeap.push(stone1 - stone2);
            }
            // 如果相等，两块石头都销毁，不需要做任何操作
        }
        
        // 返回最后的结果
        return maxHeap.empty() ? 0 : maxHeap.top();
    }
};