/*
 * 1580. Put Boxes Into the Warehouse II
 *
 * You are given two arrays of positive integers, boxes and warehouse, representing the heights of some boxes of unit width and the heights of n rooms in a warehouse respectively. The warehouse's rooms are labelled from 0 to n - 1 from left to right where warehouse[i] (0-indexed) is the height of the ith room.
 * 
 * Boxes are put into the warehouse by the following rules:
 * Boxes cannot be stacked.
 * You can rearrange the insertion order of the boxes.
 * Boxes can be pushed into the warehouse from either side (left or right)
 * If the height of some room in the warehouse is less than the height of a box, then that box and all other boxes behind it will be stopped before that room.
 * 
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
 * Output: 3
 * Explanation: 
 * Notice that it's not possible to put the box of height 4 into the warehouse since it cannot pass the first room of height 3.
 * Also, for the last two rooms, 2 and 3, only boxes of height 1 can fit.
 * We can fit 3 boxes maximum as shown above. The yellow box can also be put in room 2 instead.
 * Swapping the order of the boxes is also valid.
 * 
 * Constraints:
 * 1 <= boxes.length, warehouse.length <= 10^5
 * 1 <= boxes[i], warehouse[i] <= 10^9
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        // 将箱子按高度降序排序（从大到小）
        sort(boxes.begin(), boxes.end(), greater<int>());
        
        int n = warehouse.size();
        int res = 0;
        int left = 0, right = n - 1;
        int boxIdx = 0;
        
        // 贪心策略：优先尝试放置最大的箱子
        while (left <= right && boxIdx < boxes.size()) {
            int currentBox = boxes[boxIdx];
            
            // 尝试从左边推入
            if (currentBox <= warehouse[left]) {
                res++;
                left++;
                boxIdx++;
            }
            // 尝试从右边推入
            else if (currentBox <= warehouse[right]) {
                res++;
                right--;
                boxIdx++;
            }
            // 如果当前最大的箱子无法从任何一端推入，则跳过该箱子
            else {
                boxIdx++;
            }
        }
        
        return res;
    }
};

class Solution2 {
public:
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        int n = warehouse.size();
        
        // 预处理从左侧看的有效高度
        vector<int> leftValid(n);
        leftValid[0] = warehouse[0];
        for (int i = 1; i < n; i++) {
            leftValid[i] = min(leftValid[i - 1], warehouse[i]);
        }
        
        // 预处理从右侧看的有效高度
        vector<int> rightValid(n);
        rightValid[n - 1] = warehouse[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightValid[i] = min(rightValid[i + 1], warehouse[i]);
        }
        
        // 每个位置实际能通过的箱子高度 = 左右有效高度的最大值
        vector<int> validHeight(n);
        for (int i = 0; i < n; i++) {
            validHeight[i] = max(leftValid[i], rightValid[i]);
        }
        
        // 对有效高度和箱子高度分别排序
        sort(validHeight.begin(), validHeight.end());
        sort(boxes.begin(), boxes.end());
        
        // 贪心匹配：尽量用最小的箱子匹配最小的可用空间
        int res = 0;
        int i = 0, j = 0;
        while (i < boxes.size() && j < n) {
            if (boxes[i] <= validHeight[j]) {
                res++;
                i++;
                j++;
            } else {
                j++;
            }
        }
        
        return res;
    }
};