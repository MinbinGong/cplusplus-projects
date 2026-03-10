/**
 * 1718. Construct the Lexicographically Largest Valid Sequence
 * 
 * Given an integer n, find a sequence that satisfies all of the following:
 * 
 * The integer 1 occurs once in the sequence.
 * Each integer between 2 and n occurs twice in the sequence.
 * For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.
 * The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of their indices, |j - i|.
 * Return the lexicographically largest sequence. It is guaranteed that under the given constraints, there is always a solution.
 * 
 * A sequence a is lexicographically larger than a sequence b (of the same length) if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b. For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position they differ is at the third number, and 9 is greater than 5.
 * 
 * Example 1:
 * Input: n = 3
 * Output: [3,1,2,3,2]
 * Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.
 * 
 * Example 2:
 * Input: n = 5
 * Output: [5,3,1,4,3,5,2,4,2]
 * 
 * Constraints:
 * 1 <= n <= 20
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> constructDistancedSequence(int n) {
        int len = 2 * n - 1;                // length of the result sequence
        vector<int> res(len, 0);             // initially all zeros
        vector<bool> used(n + 1, false);     // used[i] == true if number i is already placed
        dfs(res, used, n, len);
        return res;
    }

private:
    bool dfs(vector<int>& res, vector<bool>& used, int n, int len) {
        // find the first empty position (smallest index with value 0)
        int pos = -1;
        for (int i = 0; i < len; ++i) {
            if (res[i] == 0) {
                pos = i;
                break;
            }
        }
        // if no empty position, the sequence is complete
        if (pos == -1) return true;

        // try to place numbers from largest to smallest to get lexicographically largest result
        for (int num = n; num >= 1; --num) {
            if (used[num]) continue; // number already fully placed

            if (num == 1) {
                // place the single occurrence of 1
                res[pos] = 1;
                used[1] = true;
                if (dfs(res, used, n, len)) return true;
                // backtrack
                res[pos] = 0;
                used[1] = false;
            } else {
                // for numbers > 1, we need two positions: pos and pos+num
                int second = pos + num;
                if (second < len && res[second] == 0) {
                    // place both occurrences
                    res[pos] = num;
                    res[second] = num;
                    used[num] = true;
                    if (dfs(res, used, n, len)) return true;
                    // backtrack
                    res[pos] = 0;
                    res[second] = 0;
                    used[num] = false;
                }
            }
        }
        return false; // no valid number can be placed at this position
    }
};
