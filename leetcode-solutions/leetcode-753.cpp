/*
 * 753. Cracking the Safe
 *
 * There is a box protected by a password. The password is a sequence of n digits where each digit can be one of the first k digits 0, 1, ..., k-1.
 * 
 * While entering a password, the last n digits entered will automatically be matched against the correct password.
 * 
 * For example, assuming the correct password is "345", if you type "012345", the box will open because the correct password matches the suffix of the entered password.
 * 
 * Return any password of minimum length that is guaranteed to open the box at some point of entering it.
 * 
 * Example 1:
 * 
 * Input: n = 1, k = 2
 * Output: "01"
 * Note: "10" will be accepted too.
 * 
 * Example 2:
 * 
 * Input: n = 2, k = 2
 * Output: "00110"
 * Note: "01100", "10011", "11001" will be accepted too.
 * 
 * Note:
 * 1. n will be in the range [1, 4].
 * 2. k will be in the range [1, 10].
 * 3. k^n will be at most 4096.
 * 
 */
#include <vector>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

class Solution {
public:
    string crackSafe(int n, int k) {
        // Special case n == 1: simply return all digits 0..k-1 in order
        if (n == 1) {
            string res;
            for (int i = 0; i < k; ++i)
                res.push_back('0' + i);
            return res;
        }

        // Number of nodes = k^(n-1)
        int nodeCount = 1;
        for (int i = 0; i < n - 1; ++i)
            nodeCount *= k;

        // used[node][digit] marks whether the edge from this node with that digit has been taken
        vector<vector<bool>> used(nodeCount, vector<bool>(k, false));

        stack<int> stk;
        stk.push(0);           // start from node "00...0" (n-1 zeros)
        string result;

        while (!stk.empty()) {
            int u = stk.top();
            // find the first unused digit from u
            int d = 0;
            while (d < k && used[u][d])
                ++d;

            if (d < k) {
                // take edge (u -> v) with digit d
                used[u][d] = true;
                int v = (u * k + d) % nodeCount;
                stk.push(v);
            } else {
                // no outgoing edges left from u -> backtrack
                stk.pop();
                // append the last digit of u (the node's rightmost digit)
                result.push_back('0' + (u % k));
            }
        }

        return result;
    }
};