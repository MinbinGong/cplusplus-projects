/*
 * 3Sum Smaller
 * 
 * Given an array of n integers nums and an integer target, 
 * find the number of index triplets i, j, k with 0 <= i < j < k < n 
 * that satisfy the condition nums[i] + nums[j] + nums[k] < target.
 * 
 * Example:
 * Input: nums = [-2,0,1,3], and target = 2
 * Output: 2 
 * Explanation: Because there are two triplets which sums are less than 2:
 *              [-2,0,1]
 *              [-2,0,3]
 * 
 * Note:
 * The length of the array will be in the range of [1, 200].
 * The elements in the array will be in the range of [-100, 100].
 * The target will be in the range of [-500, 500].
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        if (nums.size() < 3) return 0;
        
        sort(nums.begin(), nums.end());
        int count = 0;
        int n = nums.size();
        
        for (int i = 0; i < n - 2; i++) {
            int left = i + 1;
            int right = n - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (sum < target) {
                    // 当 nums[left] + nums[right] 满足条件时，
                    // 由于数组已排序，对于当前固定的 left，
                    // left 与从 left+1 到 right 的任意索引组合都满足条件
                    count += right - left;
                    left++; // 移动左指针寻找新的组合
                } else {
                    right--; // 和太大，减小右指针
                }
            }
        }
        
        return count;
    }
};

class Solution2 {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        if (nums.size() < 3) return 0;
        
        sort(nums.begin(), nums.end());
        int count = 0;
        int n = nums.size();
        
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                int twoSumTarget = target - nums[i] - nums[j];
                // 找到第一个大于等于 twoSumTarget 的位置
                int k = lower_bound(nums.begin() + j + 1, nums.end(), twoSumTarget) - nums.begin();
                count += k - (j + 1);
            }
        }
        
        return count;
    }
};