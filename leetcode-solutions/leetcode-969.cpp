/*
 * 969. Pancake Sorting
 *
 * Given an array of integers arr, sort the array by performing a series of pancake flips.
 *
 * In one pancake flip we do the following steps:
 *
 * Choose an integer k where 1 <= k <= arr.length.
 * Reverse the sub-array arr[0...k-1] (0-indexed).
 * For example, if arr = [3,2,1,4] and we performed a pancake flip choosing k = 3, we reverse the sub-array [3,2,1], so arr = [1,2,3,4] after the pancake flip at k = 3.
 *
 * Return an array of the k-values corresponding to a sequence of pancake flips that sort arr. Any valid answer that sorts the array within 10 * arr.length flips will be judged as correct.
 *
 * Example 1:
 *
 * Input: arr = [3,2,4,1]
 * Output: [4,2,4,3]
 * Explanation:
 * We perform 4 pancake flips, with k-values 4, 2, 4, and 3.
 * Starting state: arr = [3, 2, 4, 1]
 * After 1st flip (k = 4): arr = [1, 4, 2, 3]
 * After 2nd flip (k = 2): arr = [4, 1, 2, 3]
 * After 3rd flip (k = 4): arr = [3, 2, 1, 4]
 * After 4th flip (k = 3): arr = [1, 2, 3, 4], which is sorted.
 * 
 * Example 2:
 *
 * Input: arr = [1,2,3]
 * Output: []
 * Explanation: The input is already sorted, so there is no need to flip anything.
 * Note that other answers, such as [3, 3], would also be accepted.
 * 
 * Note:
 *
 * 1 <= arr.length <= 100
 * 1 <= arr[i] <= arr.length
 * All integers in arr are unique (i.e. arr is a permutation of the integers from 1 to arr.length).
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        vector<int> result;
        int n = arr.size();
        // 从最大值到最小值依次处理
        for (int target = n; target >= 1; --target) {
            // 找到当前目标值所在的位置
            int pos = find(arr.begin(), arr.end(), target) - arr.begin();
            // 如果已经处于正确位置（从后往前数的第 target 个），则跳过
            if (pos == target - 1) continue;
            
            // 如果不在第一个位置，先翻转到开头
            if (pos != 0) {
                result.push_back(pos + 1);
                reverse(arr.begin(), arr.begin() + pos + 1);
            }
            // 再翻转到正确位置（即前 target 个元素翻转）
            result.push_back(target);
            reverse(arr.begin(), arr.begin() + target);
        }
        return result;
    }
};