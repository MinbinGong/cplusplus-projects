/*
 * Ugly Number II
 * 
 * Write a program to find the n-th ugly number.
 * 
 * Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 
 * 
 * Example:
 * Input: n = 10
 * Output: 12
 * Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
 * 
 * Note:  
 * 1 is typically treated as an ugly number.
 * n does not exceed 1690.
 * 
 */
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution1 {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n);
        dp[0] = 1;                     // 第一个丑数是1
        int p2 = 0, p3 = 0, p5 = 0;    // 三个指针，初始都指向第一个丑数
        
        for (int i = 1; i < n; ++i) {
            // 计算三个候选丑数
            int num2 = dp[p2] * 2;
            int num3 = dp[p3] * 3;
            int num5 = dp[p5] * 5;
            
            // 取最小值作为下一个丑数
            dp[i] = min(num2, min(num3, num5));
            
            // 移动对应的指针（注意：使用三个独立的if来去重）
            if (dp[i] == num2) ++p2;
            if (dp[i] == num3) ++p3;
            if (dp[i] == num5) ++p5;
        }
        
        return dp[n - 1];
    }
};

class Solution2 {
public:
    int nthUglyNumber(int n) {
        priority_queue<long, vector<long>, greater<long>> minHeap;
        unordered_set<long> seen;
        vector<int> factors = {2, 3, 5};
        
        minHeap.push(1);
        seen.insert(1);
        long cur = 1;
        
        for (int i = 0; i < n; ++i) {
            cur = minHeap.top();
            minHeap.pop();
            
            for (int factor : factors) {
                long next = cur * factor;
                if (!seen.count(next)) {
                    seen.insert(next);
                    minHeap.push(next);
                }
            }
        }
        return cur;
    }
};