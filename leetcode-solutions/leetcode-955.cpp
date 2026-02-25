/*
 * 955. Delete Columns to Make Sorted II
 *
 * You are given an array of n strings strs, all of the same length.
 *
 * The strings can be arranged such that there is one on each line, making a grid.
 * For example, strs = ["abc", "bce", "cae"] can be arranged as:
 *
 * abc
 * bce
 * cae
 * You want to delete the columns that are not sorted lexicographically.
 * In the above example (0-indexed), columns 0 ('a', 'b', 'c') and 2 ('c', 'e', 'e') are sorted while column 1 ('b', 'c', 'a') is not, so you would delete column 1.
 *
 * Return the number of columns that you will delete.
 *
 * Example 1:
 *
 * Input: strs = ["cba","daf","ghi"]
 * Output: 1
 * Explanation: The grid looks as follows:
 *   cba
 *   daf
 *   ghi
 * 
 * Example 2:
 *
 * Input: strs = ["a","b"]
 * Output: 0
 * Explanation: The grid looks as follows:
 *   a
 *   b
 * Column 0 is the only column and is sorted, so you will not delete any columns.
 * 
 * Note:
 *
 * 1 <= n <= 100
 * 1 <= strs[i].length <= 1000
 * strs[i] consists of lowercase English letters.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();      // 字符串个数
        int m = strs[0].size();   // 字符串长度
        int deletions = 0;

        // sorted[j] 表示字符串 j 和 j+1 是否已经确定是正确排序的
        // 如果 sorted[j] = true，则后续不需要再比较这一对
        vector<bool> sorted(n - 1, false);

        // 逐列遍历
        for (int col = 0; col < m; ++col) {
            bool needDelete = false;

            // 1. 检查当前列是否会导致任何未排序的相邻对逆序
            for (int i = 0; i < n - 1; ++i) {
                if (!sorted[i] && strs[i][col] > strs[i + 1][col]) {
                    needDelete = true;
                    break;
                }
            }

            // 2. 如果当前列导致逆序，必须删除，计数加一
            if (needDelete) {
                deletions++;
                continue; // 跳过后续更新步骤，直接处理下一列
            }

            // 3. 如果当前列可以保留，则更新哪些相邻对现在已经确定为有序
            // 只有当 strs[i][col] < strs[i+1][col] 时，
            // 这一对在字典序上的关系才被最终确定（sorted[i] = true）
            for (int i = 0; i < n - 1; ++i) {
                if (!sorted[i] && strs[i][col] < strs[i + 1][col]) {
                    sorted[i] = true;
                }
            }
        }

        return deletions;
    }
};