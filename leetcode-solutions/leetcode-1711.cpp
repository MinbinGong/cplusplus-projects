/*
 * 1711. Count Good Meals
 * 
 * A good meal is a meal that contains exactly two different food items with a sum of deliciousness equal to a power of two.
 * 
 * You can pick any two different foods to make a good meal.
 * 
 * Given an array of integers deliciousness where deliciousness[i] is the deliciousness of the ith item of food, return the number of different good meals you can make from this list modulo 10^9 + 7.
 * 
 * Note that items with different indices are considered different even if they have the same deliciousness value.
 * 
 * Example 1:
 * Input: deliciousness = [1,3,5,7,9]
 * Output: 4
 * Explanation: The good meals are (1,3), (1,7), (3,5) and, (7,9).
 * Their respective sums are 4, 8, 8, and 16, all of which are powers of 2.
 * 
 * Example 2:
 * Input: deliciousness = [1,1,1,3,3,3,7]
 * Output: 15
 * Explanation: The good meals are (1,1) with 3 ways, (1,3) with 9 ways, and (1,7) with 3 ways.
 * 
 * Constraints:
 * 1 <= deliciousness.length <= 10^5
 * 0 <= deliciousness[i] <= 2^20
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countPairs(vector<int>& deliciousness) {
        const int MOD = 1e9 + 7;
        unordered_map<int, int> freq;
        for (int d : deliciousness) {
            freq[d]++;
        }

        // 所有可能的 2 的幂 (2^0 到 2^21)
        vector<int> powers;
        for (int i = 0; i <= 21; ++i) {
            powers.push_back(1 << i);
        }

        long long ans = 0;
        for (auto& [x, cntX] : freq) {
            for (int p : powers) {
                int y = p - x;
                // 只考虑 y >= x 避免重复计数
                if (freq.count(y) && y >= x) {
                    if (y == x) {
                        // 相同值，组合数为 C(cntX, 2)
                        ans = (ans + (long long)cntX * (cntX - 1) / 2) % MOD;
                    } else {
                        ans = (ans + (long long)cntX * freq[y]) % MOD;
                    }
                }
            }
        }
        return ans;
    }
};