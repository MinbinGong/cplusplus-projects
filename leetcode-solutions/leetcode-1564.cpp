/*
 * 1564. Put Boxes Into the Warehouse I
 * 
 * You are given two arrays of positive integers, boxes and warehouse, representing the heights of some boxes of unit width and the heights of n rooms in a warehouse respectively. The warehouse's rooms are labelled from 0 to n - 1 from left to right where warehouse[i] (0-indexed) is the height of the ith room.
 * 
 * Boxes are put into the warehouse by the following rules:
 * 
 * Boxes cannot be stacked.
 * You can rearrange the insertion order of the boxes.
 * Boxes can be pushed into the warehouse from either side (left or right)
 * If the height of some room in the warehouse is less than the height of a box, then that box and all other boxes behind it will be stopped before that room.
 * Return the maximum number of boxes you can put into the warehouse.
 * 
 * Example 1:
 * Input: boxes = [4,3,4,1], warehouse = [5,3,3,4,1]
 * Output: 3
 * Explanation: 
 * We can first put the box of height 1 in room 4. Then we can put the box of height 3 in either of the 3 rooms 1, 2, or 3. Lastly, we can put one box of height 4 in room 0.
 * There is no way we can fit all 4 boxes in the warehouse.
 * 
 * Example 2:
 * Input: boxes = [1,2,2,3,4], warehouse = [3,4,1,2]
 * Output: 4
 * Explanation: 
 * Notice that it is possible to put the box of height 4 in room 3.
 * First, we can put the box of height 1 in room 2. Then we can put the box of height 2 in room 1.
 * Next, we can put the box of height 3 in room 0.
 * Finally, we can put the box of height 4 in room 3.
 * 
 * Constraints:
 * n == warehouse.length
 * 1 <= boxes.length, warehouse.length <= 10^5
 * 1 <= boxes[i], warehouse[i] <= 10^9
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        // 1. 预处理仓库：每个位置的有效高度是它左边所有房间的最小值
        // 因为箱子必须经过左边的所有房间才能到达当前位置
        for (int i = 1; i < warehouse.size(); ++i) {
            warehouse[i] = min(warehouse[i], warehouse[i - 1]);
        }

        // 2. 将箱子按高度从小到大排序
        sort(boxes.begin(), boxes.end());

        // 3. 从仓库的最里面（最右边）开始尝试放置箱子
        int count = 0;  // 已放入的箱子数量
        // 从后往前遍历仓库，count 指向当前要尝试放置的箱子（从小到大）
        for (int i = warehouse.size() - 1; i >= 0 && count < boxes.size(); --i) {
            // 如果当前仓库位置的有效高度 >= 当前箱子的高度
            // 说明这个箱子可以放在这里
            if (warehouse[i] >= boxes[count]) {
                count++;  // 放置成功，尝试下一个更大的箱子
            }
            // 如果放不下，就继续往前找更大的位置（仓库位置向左移动）
        }

        return count;
    }
};