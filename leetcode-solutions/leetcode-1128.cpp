/**
 * Number of Equivalent Domino Pairs
 * 
 * Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a==c and b==d), or (a==d and b==c) - that is, one domino can be rotated to be equal to another domino.
 * 
 * Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].
 * 
 * 1 <= dominoes.length <= 40000
 * 1 <= dominoes[i][j] <= 9
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        // 使用无序映射统计每种标准化多米诺骨牌的出现次数
        unordered_map<int, int> count;
        for (auto& d : dominoes) {
            int a = d[0], b = d[1];
            // 标准化：确保较小的数字在前，组成两位数作为键
            int key = a < b ? a * 10 + b : b * 10 + a;
            ++count[key];
        }
        
        int ans = 0;
        // 对于每种等价类，从 f 个中任选两个组成一对
        for (auto& p : count) {
            int f = p.second;
            ans += f * (f - 1) / 2;
        }
        return ans;
    }
};