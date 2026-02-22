/*
 * 546. Remove Boxes
 * 
 * Given several boxes with different colors represented by different positive numbers.
 * You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1), remove them and get k*k points.
 * Find the maximum points you can get.
 * 
 * Example 1:
 * Input: boxes = [1,3,2,2,2,3,4,3,1]
 * Output: 23
 * Explanation:
 * [1, 3, 2, 2, 2, 3, 4, 3, 1]
 * ----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
 * ----> [1, 3, 3, 3, 1] (1*1=1 points)
 * ----> [1, 1] (3*3=9 points)
 * ----> [] (2*2=4 points)
 * 
 * Note:
 * The number of boxes n would not exceed 100.
 * 
 */
#include <vector>
#include <cstring>
using namespace std;

class Solution {
private:
    int dp[100][100][100]; // 记忆化数组，n <= 100

    int dfs(vector<int>& boxes, int l, int r, int k) {
        if (l > r) return 0;
        // 如果已经计算过，直接返回
        if (dp[l][r][k] != 0) return dp[l][r][k];

        // 优化：将末尾连续的相同盒子合并计算
        while (l < r && boxes[r] == boxes[r - 1]) {
            r--;
            k++;
        }

        // 记录原始的 l, r 用于保存结果
        int originalL = l, originalR = r, originalK = k;

        // 决策1：直接移除当前末尾的盒子（和右侧k个一起）
        dp[originalL][originalR][originalK] = dfs(boxes, l, r - 1, 0) + (k + 1) * (k + 1);

        // 决策2：在 [l, r-1] 中找一个与 boxes[r] 相同的盒子，合并后一起移除
        for (int i = l; i < r; i++) {
            if (boxes[i] == boxes[r]) {
                int candidate = dfs(boxes, l, i, k + 1) + dfs(boxes, i + 1, r - 1, 0);
                dp[originalL][originalR][originalK] = max(dp[originalL][originalR][originalK], candidate);
            }
        }

        return dp[originalL][originalR][originalK];
    }

public:
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        memset(dp, 0, sizeof(dp));
        return dfs(boxes, 0, n - 1, 0);
    }
};