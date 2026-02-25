/*
 * 954. Array of Doubled Pairs
 *
 * Given an integer array of even length arr, return true if it is possible to reorder arr such that arr[2 * i + 1] = 2 * arr[2 * i] for every 0 <= i < len(arr) / 2, or false otherwise.
 *
 * Example 1:
 *
 * Input: arr = [3,1,3,6]
 * Output: false
 *
 * Example 2:
 *
 * Input: arr = [2,1,2,6]
 * Output: false
 *
 * Example 3:
 *
 * Input: arr = [4,-2,2,-4]
 * Output: true
 * Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or [2,4,-2,-4].
 *
 * Note:
 *
 * 2 <= arr.length <= 3 * 104
 * arr.length is even.
 * -105 <= arr[i] <= 105
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        unordered_map<int, int> count;
        for (int x : arr) count[x]++;
        
        vector<int> keys;
        for (auto& p : count) keys.push_back(p.first);
        sort(keys.begin(), keys.end(), [](int a, int b) {
            return abs(a) < abs(b);
        });
        
        for (int x : keys) {
            if (count[x] == 0) continue;
            if (x == 0) {
                if (count[0] % 2 != 0) return false;
                count[0] = 0;
            } else {
                int need = 2 * x;
                if (count[need] < count[x]) return false;
                count[need] -= count[x];
                count[x] = 0; // optional
            }
        }
        return true;
    }
};