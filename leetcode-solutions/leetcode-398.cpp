/*
 * Random Pick Index
 * 
 * Given an integer array nums with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.
 * 
 * Implement the Solution class:
 * 
 * Solution(int[] nums) Initializes the object with the array nums.
 * int pick(int target) Picks a random index i from nums where nums[i] == target. If there are multiple valid i's, then each index should have an equal probability of returning.
 * 
 * Example 1:
 * Input
 * ["Solution", "pick", "pick", "pick"]
 * [[[1, 2, 3, 3, 3]], [3], [1], [3]]
 * Output
 * [null, 4, 0, 2]
 * 
 * Explanation
 * Solution solution = new Solution([1, 2, 3, 3, 3]);
 * solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 */
#include <vector>
using namespace std;

class Solution {
private:
    vector<int> nums;
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
    }
    
    int pick(int target) {
        int count = 0;
        int res = -1;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == target) {
                count++;
                // 以 1/count 的概率选择当前索引
                if (rand() % count == 0) {
                    res = i;
                }
            }
        }
        return res;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */