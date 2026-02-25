/*
 * 1007. Minimum Domino Rotations For Equal Row
 *
 * In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the i-th domino.  (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
 *
 * We may rotate the i-th domino, so that A[i] and B[i] swap values.
 *
 * Return the minimum number of rotations so that all the values in A are the same, or all the values in B are the same.
 *
 * If it cannot be done, return -1.
 *
 * Example 1:
 *
 * Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
 * Output: 2
 * Explanation: 
 * The first figure represents the dominoes as given by A and B: before we do any rotations.
 * 
 * Example 2:
 *
 * Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
 * Output: -1
 * Explanation: 
 * In this case, it is not possible to rotate the dominoes to make one row of values equal.
 * 
 * Note:
 *
 * 1 <= A[i], B[i] <= 6
 * 2 <= A.length == B.length <= 20000
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        int n = A.size();
        
        // Helper to check for a given target value x
        auto check = [&](int x) -> int {
            int rotationsTop = 0;   // rotations needed to make all tops = x
            int rotationsBottom = 0; // rotations needed to make all bottoms = x
            for (int i = 0; i < n; ++i) {
                if (A[i] != x && B[i] != x) {
                    return -1; // impossible
                }
                if (A[i] != x) ++rotationsTop;      // need to rotate to bring x to top
                if (B[i] != x) ++rotationsBottom;   // need to rotate to bring x to bottom
            }
            return min(rotationsTop, rotationsBottom);
        };
        
        // Try the two candidates: A[0] and B[0]
        int res1 = check(A[0]);
        int res2 = check(B[0]);
        
        if (res1 == -1 && res2 == -1) return -1;
        if (res1 == -1) return res2;
        if (res2 == -1) return res1;
        return min(res1, res2);
    }
};