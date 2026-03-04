/*
 * 1521. Find a Value of a Mysterious Function Closest to Target
 *
 * Winston was given the above mysterious function func. He has an integer array arr and an integer target and he wants to find the values l and r that make the value |func(arr, l, r) - target| minimum possible.
 *
 * Return the minimum possible value of |func(arr, l, r) - target|.
 *
 * Notice that func should be called with the values l and r where 0 <= l, r < arr.length.
 *
 * Example 1:
 * Input: arr = [9,12,3,7,15], target = 5
 * Output: 2
 * Explanation: Calling func with all the pairs of [l,r] = [[0,0],[1,1],[2,2],[3,3],[4,4],[0,1],[1,2],[2,3],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[0,4]], Winston got the following results [9,12,3,7,15,8,0,3,7,0,0,3,0,0,0]. The value closest to 5 is 7 and 3, thus the minimum difference is 2.
 * 
 * Example 2:
 * Input: arr = [1000000,1000000,1000000], target = 1
 * Output: 999999
 * Explanation: Winston called the func with all possible values of [l,r] and he always got 1000000, thus the minimum difference is 999999.
 * 
 * Constraints:
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 10^6
 * 0 <= target <= 10^7
 * 
 */
#include <vector>
#include <climits>
#include <cstdlib>   // for abs

class Solution {
public:
    int closestToTarget(std::vector<int>& arr, int target) {
        int ans = INT_MAX;
        std::vector<int> cur;                     // distinct ANDs for subarrays ending at previous index

        for (int x : arr) {
            std::vector<int> nxt;
            nxt.push_back(x);                      // subarray consisting only of x

            for (int v : cur) {
                int a = v & x;
                if (a != nxt.back()) {             // keep values distinct (non‑increasing order)
                    nxt.push_back(a);
                }
            }

            for (int v : nxt) {
                int diff = std::abs(v - target);
                if (diff < ans) ans = diff;
                if (ans == 0) return 0;            // early exit if exact match found
            }

            cur = std::move(nxt);
        }

        return ans;
    }
};