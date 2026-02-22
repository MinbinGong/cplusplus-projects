/*
 * 526. Beautiful Arrangement
 *
 * Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is constructed by these N numbers successfully if one of the following is true for the ith position (1 <= i <= N) in this array:
 * 1. The number at the ith position is divisible by i.
 * 2. i is divisible by the number at the ith position.
 * 
 * Now given N, how many beautiful arrangements can you construct?
 * 
 * Example 1:
 * Input: 2
 * Output: 2
 * Explanation: 
 * The first beautiful arrangement is [1, 2]:
 * Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).
 * Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).
 * 
 * The second beautiful arrangement is [2, 1]:
 * Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).
 * Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
 * 
 * Note:
 * N is a positive integer and will not exceed 15.
 * 
 */
#include <vector>
using namespace std;

class Solution1 {
public:
    int countArrangement(int n) {
        vector<bool> used(n + 1, false);
        return backtrack(1, n, used);
    }
    
private:
    int backtrack(int pos, int n, vector<bool>& used) {
        if (pos > n) return 1;               // all positions filled → valid arrangement
        
        int count = 0;
        for (int num = 1; num <= n; ++num) {
            if (!used[num] && (num % pos == 0 || pos % num == 0)) {
                used[num] = true;
                count += backtrack(pos + 1, n, used);
                used[num] = false;
            }
        }
        return count;
    }
};

class Solution2 {
public:
    int countArrangement(int n) {
        vector<vector<int>> candidates(n + 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i % j == 0 || j % i == 0) {
                    candidates[i].push_back(j);
                }
            }
        }
        vector<bool> used(n + 1, false);
        return dfs(1, n, used, candidates);
    }
    
private:
    int dfs(int pos, int n, vector<bool>& used, vector<vector<int>>& candidates) {
        if (pos > n) return 1;
        int count = 0;
        for (int num : candidates[pos]) {
            if (!used[num]) {
                used[num] = true;
                count += dfs(pos + 1, n, used, candidates);
                used[num] = false;
            }
        }
        return count;
    }
};