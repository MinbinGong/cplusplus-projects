/**
 * 1492. The kth Factor of n
 * 
 * Given two positive integers n and k.
 * 
 * A factor of an integer n is defined as an integer i where n % i == 0.
 * 
 * Consider a list of all factors of n sorted in ascending order, return the kth factor in this list or return -1 if n has less than k factors.
 * 
 * Example 1:
 * Input: n = 12, k = 3
 * Output: 3
 * Explanation: Factors list is [1, 2, 3, 4, 6, 12], the 3rd factor is 3.
 * 
 * Example 2:
 * Input: n = 7, k = 2
 * Output: 7
 * Explanation: Factors list is [1, 7], the 2nd factor is 7.
 * 
 * Example 3:
 * Input: n = 4, k = 4
 * Output: -1
 * Explanation: Factors list is [1, 2, 4], there are only 3 factors. We should return -1.
 * 
 * Constraints:
 * 1 <= k <= n <= 1000
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int kthFactor(int n, int k) {
        vector<int> factors;
        // 遍历到 sqrt(n) 收集所有因子
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                factors.push_back(i);
                if (i != n / i) {
                    factors.push_back(n / i);
                }
            }
        }
        // 排序得到升序序列
        sort(factors.begin(), factors.end());
        if (k > factors.size()) return -1;
        return factors[k - 1];
    }
};