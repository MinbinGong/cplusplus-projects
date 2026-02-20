/*
 * Intersection of Two Arrays
 * 
 * Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.
 * 
 * Example 1:
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 * 
 * Example 2:
 * Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * Output: [9,4]
 * Explanation: [4,9] is also accepted.
 * 
 * Constraints:
 * 1 <= nums1.length, nums2.length <= 1000
 * 0 <= nums1[i], nums2[i] <= 1000
 * 
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // 将 nums1 的元素存入哈希集合，便于快速查找
        unordered_set<int> set1(nums1.begin(), nums1.end());
        unordered_set<int> resultSet;

        // 遍历 nums2，如果当前元素在 set1 中出现，则加入结果集合
        for (int num : nums2) {
            if (set1.find(num) != set1.end()) {
                resultSet.insert(num);
            }
        }

        // 将结果集合转换为向量返回
        return vector<int>(resultSet.begin(), resultSet.end());
    }
};