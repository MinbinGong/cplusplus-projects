/**
 * 862. Shortest Subarray with Sum at Least K
 * 
 * Example 1:
 * Input: A = [1], K = 1
 * Output: 1
 * 
 * Example 2:
 * Input: A = [1,2], K = 4
 * Output: -1
 * 
 * Example 3:
 * Input: A = [2,-1,2], K = 3
 * Output: 3
 * 
 * Note:
 * 1 <= A.length <= 50000
 * -10 ^ 5 <= A[i] <= 10 ^ 5
 * 1 <= K <= 10 ^ 9
 * 
 */
#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        int n = A.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + A[i];
        }
        deque<int> dq;
        int ans = n + 1;
        for (int i = 0; i <= n; ++i) {
            // 检查是否有以 i 结尾的满足条件的子数组
            while (!dq.empty() && prefix[i] - prefix[dq.front()] >= K) {
                ans = min(ans, i - dq.front());
                dq.pop_front();
            }
            // 维护单调递增队列（按 prefix 值）
            while (!dq.empty() && prefix[dq.back()] >= prefix[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        return ans == n + 1 ? -1 : ans;
    }
};