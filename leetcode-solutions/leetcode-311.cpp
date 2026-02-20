/*
 * Sparse Matrix Multiplication
 * 
 * Given two sparse matrices mat1 of size m x k and mat2 of size k x n, return the result of mat1 x mat2.
 * You may assume that multiplication is always possible.
 *
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        int m = mat1.size();          // mat1的行数
        int n = mat1[0].size();       // mat1的列数 = mat2的行数
        int p = mat2[0].size();       // mat2的列数
        
        // 初始化结果矩阵，大小为 m x p，所有元素为0
        vector<vector<int>> result(m, vector<int>(p, 0));
        
        // 核心优化：只对非零元素进行计算
        for (int i = 0; i < m; i++) {              // 遍历mat1的每一行
            for (int k = 0; k < n; k++) {          // 遍历mat1的每一列（同时也是mat2的行索引）
                if (mat1[i][k] != 0) {              // 关键：只有当mat1[i][k]非零时才进行计算
                    for (int j = 0; j < p; j++) {   // 遍历mat2的每一列
                        // 这里可以再加一层判断：if (mat2[k][j] != 0) 
                        // 但实验表明，跳过mat1的零元素已经能带来显著的性能提升
                        result[i][j] += mat1[i][k] * mat2[k][j];
                    }
                }
            }
        }
        
        return result;
    }
};