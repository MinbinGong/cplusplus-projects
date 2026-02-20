/*
 * Ugly Number II
 * 
 * An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
 * 
 * Given an integer n, return the nth ugly number.
 * 
 * Example 1:
 * Input: n = 12
 * Output: 12
 * Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 12 ugly numbers.
 * 
 * Example 2:
 * Input: n = 1
 * Output: 1
 * Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.
 * 
 */
#include <algorithm>
#include <vector>
using namespace std;

// int nthSuperUglyNumber(int n, vector<int> &primes) {
//   vector<int> cpr(primes.begin(), primes.end());
//   vector<int> ind(primes.size(), 0);
//   vector<long long> dp(n + 1);
//   dp[0] = 1;
//   for (int i = 1; i < n; ++i) {
//     long long int m = 1e18;
//     for (auto p : primes) {
//       m = min(m, (long long)p);
//     }
//     dp[i] = m;
//     for (int j = 0; j < primes.size(); j++) {
//       if (m == primes[j]) {
//         ind[j]++;
//         primes[j] = dp[ind[j]] * cpr[j];
//       }
//     }
//   }
//   return dp[n - 1];
// }

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        // dp 数组存储丑数序列
        vector<long> dp(n, 0);
        dp[0] = 1;
        
        // 指针数组，记录每个质数当前乘到了dp数组的哪个位置
        vector<int> pointers(primes.size(), 0);
        
        // 记录每个质数下一次可能产生的丑数值
        vector<long> nums(primes.size(), 1);
        // 初始化 nums 为质数本身
        for (int i = 0; i < primes.size(); i++) {
            nums[i] = primes[i];
        }
        
        for (int i = 1; i < n; i++) {
            // 找出当前所有候选值中的最小值
            long minVal = LONG_MAX;
            for (int j = 0; j < primes.size(); j++) {
                if (nums[j] < minVal) {
                    minVal = nums[j];
                }
            }
            
            // 最小值即为下一个丑数
            dp[i] = minVal;
            
            // 更新所有产生这个最小值的指针
            for (int j = 0; j < primes.size(); j++) {
                if (nums[j] == minVal) {
                    pointers[j]++;
                    nums[j] = dp[pointers[j]] * primes[j];
                }
            }
        }
        
        return dp[n - 1];
    }
};