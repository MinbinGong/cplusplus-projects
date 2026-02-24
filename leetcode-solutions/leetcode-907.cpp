/*
 * Sum of Subarray Minimums
 *
 * Given an array of integers A, find the sum of min(B), where B ranges over every (contiguous) subarray of A.
 * 
 * Since the answer may be large, return the answer modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: [3,1,2,4]
 * Output: 17
 * Explanation: Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
 * Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.  Sum is 17.
 * 
 * Note:
 * 1 <= A.length <= 30000
 * 1 <= A[i] <= 30000
 */
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int n = arr.size();
        vector<int> left(n), right(n);
        stack<int> st;

        // previous smaller (strictly less)
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && arr[st.top()] >= arr[i]) {
                st.pop();
            }
            left[i] = st.empty() ? i + 1 : i - st.top();
            st.push(i);
        }

        // clear stack for next pass
        while (!st.empty()) st.pop();

        // next smaller or equal (to avoid duplicate counting)
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && arr[st.top()] > arr[i]) {
                st.pop();
            }
            right[i] = st.empty() ? n - i : st.top() - i;
            st.push(i);
        }

        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = (ans + (long long)arr[i] * left[i] * right[i]) % MOD;
        }
        return ans;
    }
};