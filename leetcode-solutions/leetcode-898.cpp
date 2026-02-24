/**
 * 898. Bitwise ORs of Subarrays
 *
 * We have an array A of non-negative integers.
 * For every (contiguous) subarray B = [A[i], A[i+1], ..., A[j]] (with i <= j), we take the bitwise OR of all the elements in B, obtaining a result A[i] | A[i+1] | ... | A[j].
 * Return the number of possible results.  (Results that occur more than once are only counted once in the final answer.)
 *
 * Example 1:
 * Input: [0]
 * Output: 1
 * Explanation: 
 * There is only one possible result: 0.
 *
 * Example 2:
 * Input: [1,1,2]
 * Output: 3
 * Explanation: 
 * The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
 * These yield the results 1, 1, 2, 1, 3, 3.
 * There are 3 unique values, so the answer is 3.
 *
 * Example 3:
 * Input: [1,2,4]
 * Output: 6
 * Explanation: 
 * The possible results are 1, 2, 3, 4, 6, and 7.
 *
 * Note:
 * 1 <= A.length <= 50000
 * 0 <= A[i] <= 10^9
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        unordered_set<int> all;      // 存储所有子数组的 OR 结果
        unordered_set<int> prev;     // 存储以当前位置前一个元素结尾的所有子数组的 OR 结果

        for (int num : arr) {
            unordered_set<int> curr; // 存储以当前元素结尾的所有子数组的 OR 结果
            curr.insert(num);        // 只有当前元素本身构成的子数组
            // 将前一个位置的所有 OR 结果与当前元素组合，得到新的子数组 OR
            for (int val : prev) {
                curr.insert(val | num);
            }
            // 将当前结果加入全局集合
            all.insert(curr.begin(), curr.end());
            // 更新 prev 为 curr，供下一轮使用
            prev = move(curr);
        }

        return all.size();
    }
};