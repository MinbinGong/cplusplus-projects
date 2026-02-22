/*
 * Split Array into Consecutive Subsequences
 *
 * You are given an integer array sorted in ascending order (may contain duplicates), you need to split them into several subsequences, where each subsequences consist of at least 3 consecutive integers. Return whether you can make such a split.
 *
 * Example 1:
 *
 * Input: [1,2,3,3,4,5]
 * Output: True
 * Explanation:
 * You can split them into two consecutive subsequences : 
 * 1, 2, 3
 * 3, 4, 5
 *
 * Example 2:
 *
 * Input: [1,2,3,3,4,4,5,5]
 * Output: True
 * Explanation:
 * You can split them into two consecutive subsequences : 
 * 1, 2, 3, 4, 5
 * 3, 4, 5
 *
 * Example 3:
 *
 * Input: [1,2,3,4,4,5]
 * Output: False
 *
 * Note:
 * 
 * The length of the input is in range of [1, 10000]
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int, int> freq, need;
        for (int num : nums) freq[num]++;
        for (int num : nums) {
            if (freq[num] == 0) continue;          // already used
            if (need[num] > 0) {                    // can append to an existing subsequence
                need[num]--;
                need[num + 1]++;
                freq[num]--;
            } else if (freq[num + 1] > 0 && freq[num + 2] > 0) { // start a new subsequence
                freq[num]--;
                freq[num + 1]--;
                freq[num + 2]--;
                need[num + 3]++;
            } else {
                return false;
            }
        }
        return true;
    }
};