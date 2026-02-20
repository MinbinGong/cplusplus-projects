/*
 * Range Sum Query 2D - Mutable
 * 
 * Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
 * 
 * The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.
 * 
 * Example:
 * Given matrix = [
 *   [3, 0, 1, 4, 2],
 *   [5, 6, 3, 2, 1],
 *   [1, 2, 0, 1, 5],
 *   [4, 1, 0, 1, 7],
 *   [1, 0, 3, 0, 5]
 * ]
 * 
 * sumRegion(2, 1, 4, 3) -> 8
 * update(3, 2, 2)
 * sumRegion(2, 1, 4, 3) -> 10
 * 
 */
#include <vector>
using namespace std;

class NumMatrix {
private:
    int m, n;
    vector<vector<int>> tree; // 二维树状数组 (1-indexed)
    vector<vector<int>> nums; // 保存原始矩阵的副本，用于计算差值

    // 二维树状数组的低位操作 - 查询前缀和 (从(0,0)到(row,col)的和)
    int prefixSum(int row, int col) {
        int sum = 0;
        // 树状数组索引需要+1，因为tree是1-indexed
        for (int i = row + 1; i > 0; i -= (i & -i)) {
            for (int j = col + 1; j > 0; j -= (j & -j)) {
                sum += tree[i][j];
            }
        }
        return sum;
    }

public:
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        
        m = matrix.size();
        n = matrix[0].size();
        
        // 初始化树状数组，大小为(m+1) x (n+1)，因为树状数组通常使用1-indexed
        tree.assign(m + 1, vector<int>(n + 1, 0));
        nums.assign(m, vector<int>(n, 0));
        
        // 将矩阵中的每个元素插入树状数组
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                update(i, j, matrix[i][j]);
            }
        }
    }
    
    void update(int row, int col, int val) {
        // 计算变化量delta = 新值 - 旧值
        int delta = val - nums[row][col];
        nums[row][col] = val;
        
        // 二维树状数组更新操作：更新所有包含(row, col)的前缀和
        for (int i = row + 1; i <= m; i += (i & -i)) {
            for (int j = col + 1; j <= n; j += (j & -j)) {
                tree[i][j] += delta;
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        // 使用容斥原理计算矩形区域和
        // sumRegion = prefixSum(row2, col2) - prefixSum(row1-1, col2) 
        //             - prefixSum(row2, col1-1) + prefixSum(row1-1, col1-1)
        return prefixSum(row2, col2) - prefixSum(row1 - 1, col2) 
             - prefixSum(row2, col1 - 1) + prefixSum(row1 - 1, col1 - 1);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */