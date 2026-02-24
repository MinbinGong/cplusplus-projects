/**
 * 835. Image Overlap
 * 
 * Two images A and B are given, represented as binary, square matrices of the same size.  (A binary matrix has only 0s and 1s as values.)
 * 
 * We translate one image however we choose (sliding it left, right, up, or down any number of units), and place it on top of the other image.  After, the overlap of this translation is the number of positions that have a 1 in both images.
 * 
 * (Note also that a translation does not include any kind of rotation.)
 * 
 * What is the largest possible overlap?
 * 
 * Example:
 * Input: A = [[1,1,0],[0,1,0],[0,1,0]]
 *        B = [[0,0,0],[0,1,1],[0,0,1]]
 * Output: 3
 * Explanation: We slide A to right by 1 unit and down by 1 unit.
 * 
 * Notes: 
 * 1 <= A.length = A[0].length = B.length = B[0].length <= 30
 * 0 <= A[i][j], B[i][j] <= 1
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        int n = A.size();
        int ans = 0;
        // Try all possible shifts: dx and dy from -(n-1) to n-1
        for (int dx = -n + 1; dx < n; ++dx) {
            for (int dy = -n + 1; dy < n; ++dy) {
                int cnt = 0;
                for (int i = 0; i < n; ++i) {
                    int ni = i + dx;
                    if (ni < 0 || ni >= n) continue;
                    for (int j = 0; j < n; ++j) {
                        int nj = j + dy;
                        if (nj < 0 || nj >= n) continue;
                        if (A[i][j] == 1 && B[ni][nj] == 1)
                            ++cnt;
                    }
                }
                ans = max(ans, cnt);
            }
        }
        return ans;
    }
};