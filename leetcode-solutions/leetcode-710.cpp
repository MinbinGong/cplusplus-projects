/*
 * Random Pick with Blacklist
 * 
 * Given a blacklist B containing unique integers from [0, N), write a function to return a uniform random integer from [0, N) which is NOT in B.
 * 
 * Optimize it such that it minimizes the call to system’s Math.random().
 * 
 * Note:
 * 1. 1 <= N <= 1000000000
 * 2. 0 <= B.length < min(100000, N)
 * 3. [0, N) does NOT include N. See interval notation.
 * 4. The input parameter N is an integer.
 * 5. B is an array of integers.
 * 6. B is sorted in ascending order.
 * 7. B[i] is an integer in the range [0, N).
 * 
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
private:
    int m; // 合法数的个数，也是随机范围 [0, m-1]
    unordered_map<int, int> mapping; // 黑名单数到合法数的映射

public:
    Solution(int n, vector<int>& blacklist) {
        unordered_set<int> blackSet(blacklist.begin(), blacklist.end());
        m = n - blacklist.size();
        int j = m; // 从 m 开始寻找可用的替换数
        for (int b : blacklist) {
            if (b < m) { // 只有在前 m 个数中的黑名单数才需要映射
                while (blackSet.count(j)) ++j; // 跳过也在黑名单中的数
                mapping[b] = j;
                ++j;
            }
        }
    }
    
    int pick() {
        int x = rand() % m;
        return mapping.count(x) ? mapping[x] : x;
    }
};