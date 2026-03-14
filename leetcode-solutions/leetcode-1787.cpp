/**
 * 1787. Make the XOR of All Segments Equal to Zero
 * 
 * You are given an array nums and an integer k. The XOR of a segment [left, right] where left <= right is the XOR of all the elements with indices between left and right, inclusive: nums[left] XOR nums[left+1] XOR ... XOR nums[right].
 * 
 * Return the minimum number of elements to change in the array such that the XOR of all segments of size k is equal to zero.
 * 
 *  
 * 
 * Example 1:
 * 
 * Input: nums = [1,2,0,3,0], k = 1
 * Output: 3
 * Explanation: Modify the array from [1,2,0,3,0] to from [0,0,0,0,0].
 * Example 2:
 * 
 * Input: nums = [3,4,5,2,1,7,3,4,7], k = 3
 * Output: 3
 * Explanation: Modify the array from [3,4,5,2,1,7,3,4,7] to [3,4,7,3,4,7,3,4,7].
 * Example 3:
 * 
 * Input: nums = [1,2,4,1,2,5,1,2,6], k = 3
 * Output: 3
 * Explanation: Modify the array from [1,2,4,1,2,5,1,2,6] to [1,2,3,1,2,3,1,2,3].
 *  
 * 
 * Constraints:
 * 
 * 1 <= k <= nums.length <= 2000
 * 0 <= nums[i] < 210
 * 
 */
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        const int M = 1024;               // numbers are in [0, 1023]
        const int INF = 1e9;
        int n = nums.size();

        // group indices by residue modulo k
        vector<vector<int>> classes(k);
        for (int i = 0; i < n; ++i) {
            classes[i % k].push_back(nums[i]);
        }

        vector<int> dp(M, INF);
        dp[0] = 0;                         // before any class, XOR = 0 with cost 0

        for (int r = 0; r < k; ++r) {
            int sz = classes[r].size();
            vector<int> freq(M, 0);
            for (int val : classes[r]) {
                ++freq[val];
            }

            // distinct values that appear in this class
            vector<int> appear;
            for (int v = 0; v < M; ++v) {
                if (freq[v] > 0) appear.push_back(v);
            }
            int L = appear.size();

            vector<int> new_dp(M, INF);

            // ----- transitions for values that actually appear -----
            for (int v : appear) {
                int cost = sz - freq[v];
                for (int x = 0; x < M; ++x) {
                    if (dp[x] == INF) continue;
                    int nx = x ^ v;
                    if (dp[x] + cost < new_dp[nx]) {
                        new_dp[nx] = dp[x] + cost;
                    }
                }
            }

            // ----- transitions for all other values (cost = sz) -----
            if (L <= M - L) {   // use method "per target t" – O(M * L)
                // list of indices with finite dp, sorted by dp value
                vector<int> order;
                for (int x = 0; x < M; ++x) {
                    if (dp[x] != INF) order.push_back(x);
                }
                sort(order.begin(), order.end(),
                     [&](int a, int b) { return dp[a] < dp[b]; });

                vector<int> last_used(M, 0);
                int cur_time = 0;
                for (int t = 0; t < M; ++t) {
                    ++cur_time;
                    // mark indices forbidden for this t (they would come from an appearing value)
                    for (int a : appear) {
                        int x = t ^ a;
                        last_used[x] = cur_time;
                    }
                    // find first allowed index with smallest dp
                    int best_x = -1;
                    for (int x : order) {
                        if (last_used[x] != cur_time) {
                            best_x = x;
                            break;
                        }
                    }
                    if (best_x != -1) {
                        int cand = sz + dp[best_x];
                        if (cand < new_dp[t]) {
                            new_dp[t] = cand;
                        }
                    }
                }
            } else {             // use method "iterate over non‑appearing values" – O(M * (M-L))
                vector<bool> is_appear(M, false);
                for (int v : appear) is_appear[v] = true;
                for (int v = 0; v < M; ++v) {
                    if (is_appear[v]) continue;
                    int cost = sz;
                    for (int x = 0; x < M; ++x) {
                        if (dp[x] == INF) continue;
                        int nx = x ^ v;
                        if (dp[x] + cost < new_dp[nx]) {
                            new_dp[nx] = dp[x] + cost;
                        }
                    }
                }
            }

            dp = move(new_dp);
        }

        return dp[0];
    }
};