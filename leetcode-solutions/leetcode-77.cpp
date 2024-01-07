/*
    题目描述
        给定一个整数 n 和一个整数 k，求在 1 到 n 中选取 k 个数字的所有组合方法

    题解
        类似于排列问题，我们也可以进行回溯。排列回溯的是交换的位置，而组合回溯的是否把当
    前的数字加入结果中。
 */
#include <vector>
using namespace std;

void backtracking(vector<vector<int>>& ans, vector<int>& comb, int count, int pos, int n, int k) {
    if (count == k) {
        ans.push_back(comb);
        return;
    }

    for (int i = pos; i <= n; ++i) {
        comb[count++] = 1;
        backtracking(ans, comb, count, i + 1, n, k);
        --count;
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> ans;
    vector<int> comb;
    int count = 0;
    backtracking(ans, comb, count, 1, n, k);
    return ans;
}