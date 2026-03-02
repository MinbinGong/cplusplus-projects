/*
 * 1354. Construct Target Array With Multiple Sums
 * 
 * Given an array of integers target. From a starting array, A consisting of all 1's, you may perform the following procedure :
 * 
 * let x be the sum of all elements currently in your array.
 * choose index i, such that 0 <= i < target.size and set the value of A at index i to x.
 * You may repeat this procedure as many times as needed.
 * Return True if it is possible to construct the target array from A otherwise return False.
 * 
 * Example 1:
 * Input: target = [9,3,5]
 * Output: true
 * Explanation: Start with [1, 1, 1] 
 * [1, 1, 1], sum = 3 choose index 1
 * [1, 3, 1], sum = 5 choose index 2
 * [1, 3, 5], sum = 9 choose index 0
 * [9, 3, 5] Done
 * 
 * Example 2:
 * Input: target = [1,1,1,2]
 * Output: false
 * Explanation: Impossible to create target array from [1,1,1,1].
 * 
 * Example 3:
 * Input: target = [8,5]
 * Output: true
 * 
 * Note:
 * 1 <= target.length <= 10^5
 * 1 <= target[i] <= 10^9
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    bool isPossible(vector<int>& target) {
        int n = target.size();
        // Single element case: must be 1
        if (n == 1) return target[0] == 1;

        // Use a max heap to always process the largest value
        priority_queue<long long> pq;
        long long total = 0;
        for (int x : target) {
            pq.push(x);
            total += x;
        }

        while (pq.top() > 1) {
            long long maxVal = pq.top();
            pq.pop();
            long long rest = total - maxVal;   // sum of all other elements

            // In a valid reverse step, the largest element must be > sum of others
            if (maxVal <= rest) return false;

            // Compute the value that was replaced to obtain maxVal
            long long newVal = maxVal % rest;
            if (newVal == 0) newVal = rest;    // multiple of rest -> must become rest itself

            // Update total and push the new value
            total = rest + newVal;
            pq.push(newVal);
        }
        return true;
    }
};