/*
 * 996. Number of Squareful Arrays
 * 
 * Given an array A of non-negative integers, the array is squareful if for every pair of adjacent elements, their sum is a perfect square.
 *
 * Return the number of permutations of A that are squareful.  Two permutations perm1 and perm2 differ if and only if there is some index i such that perm1[i] != perm2[i].
 *
 * Example 1:
 *
 * Input: [1,17,8]
 * Output: 2
 * Explanation:
 * [1,8,17] and [17,8,1] are the valid permutations.
 *
 * Example 2:
 *
 * Input: [2,2,2]
 * Output: 1
 *
 * Note:
 *
 * 1 <= A.length <= 12
 * 0 <= A[i] <= 1e9
 */
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

class Solution {
public:
    int numSquarefulPerms(vector<int>& A) {
        sort(A.begin(), A.end());
        int n = A.size();
        vector<bool> used(n, false);
        int ans = 0;
        
        // Helper to check if a number is a perfect square
        auto isPerfectSquare = [](int x) {
            int r = static_cast<int>(sqrt(x));
            return r * r == x || (r + 1) * (r + 1) == x;
        };
        
        function<void(int, int)> backtrack = [&](int count, int prev) {
            if (count == n) {
                ++ans;
                return;
            }
            for (int i = 0; i < n; ++i) {
                if (used[i]) continue;
                // Skip duplicates: if current equals previous and previous was not used
                if (i > 0 && A[i] == A[i-1] && !used[i-1]) continue;
                
                if (count == 0 || isPerfectSquare(prev + A[i])) {
                    used[i] = true;
                    backtrack(count + 1, A[i]);
                    used[i] = false;
                }
            }
        };
        
        backtrack(0, 0);
        return ans;
    }
};