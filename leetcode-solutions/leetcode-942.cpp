/*
 * DI String Match
 *
 * Given a string S that only contains "I" (increase) or "D" (decrease), let N = S.length.
 *
 * Return any permutation A of [0, 1, ..., N] such that for all i = 0, ..., N-1:
 *
 * If S[i] == "I", then A[i] < A[i+1]
 * If S[i] == "D", then A[i] > A[i+1]
 * 
 * Example 1:
 * Input: "IDID"
 * Output: [0,4,1,3,2]
 * 
 * Example 2:
 * Input: "III"
 * Output: [0,1,2,3]
 * 
 * Example 3:
 * Input: "DDI"
 * Output: [3,2,0,1]
 * 
 * Note:
 * 1 <= S.length <= 10000
 * S only contains characters "I" or "D".
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> diStringMatch(string s) {
        int n = s.size();
        int low = 0, high = n;
        vector<int> perm;
        perm.reserve(n + 1);

        for (char c : s) {
            if (c == 'I') {
                perm.push_back(low++);
            } else { // c == 'D'
                perm.push_back(high--);
            }
        }
        // 最后放入剩下的唯一数字（此时 low == high）
        perm.push_back(low);

        return perm;
    }
};