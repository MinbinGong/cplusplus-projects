/*
 * Delete Columns to Make Sorted
 *
 * We are given an array A of N lowercase letter strings, all of the same length.
 *
 * Now, we may choose any set of deletion indices, and for each string, we delete all the characters in those indices.
 *
 * For example, if we have an array A = ["abcdef","uvwxyz"] and deletion indices {0, 2, 3}, then the final array after deletions is ["bef","vyz"].
 *
 * Suppose we chose a set of deletion indices D such that after deletions, the final array has its elements in lexicographic order (A[0] <= A[1] <= A[2] ... <= A[A.length - 1]).
 *
 * Return the minimum possible value of D.length.
 *
 * Example 1:
 * Input: ["cba","daf","ghi"]
 * Output: 1
 * Explanation:
 * After choosing D = {1}, each column ["c","d","g"] and ["a","f","i"] are in lexicographic order.
 * 
 * Example 2:
 * Input: ["a","b"]
 * Output: 0
 * Explanation: D = {}
 * 
 * Example 3:
 * Input: ["zyx","wvu","tsr"]
 * Output: 3
 * Explanation: D = {0, 1, 2}
 * 
 * Note:
 * 1 <= A.length <= 100
 * 1 <= A[i].length <= 1000
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int rows = strs.size();
        if (rows == 0) return 0;
        int cols = strs[0].size();
        int deleteCount = 0;
        
        for (int j = 0; j < cols; ++j) {
            for (int i = 1; i < rows; ++i) {
                if (strs[i][j] < strs[i-1][j]) {
                    deleteCount++;
                    break;
                }
            }
        }
        return deleteCount;
    }
};