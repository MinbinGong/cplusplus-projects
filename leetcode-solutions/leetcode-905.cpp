/*
 * Sort Array By Parity
 * 
 * Given an array A of non-negative integers, return an array consisting of all the even elements of A,
 * followed by all the odd elements of A.
 * 
 * You may return any answer array that satisfies this condition.
 * 
 * Example 1:
 * Input: [3,1,2,4]
 * Output: [2,4,3,1]
 * The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
 * 
 * Note:
 * 1 <= A.length <= 5000
 * 0 <= A[i] <= 5000
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            // move left until odd
            while (left < right && nums[left] % 2 == 0) left++;
            // move right until even
            while (left < right && nums[right] % 2 == 1) right--;
            if (left < right) {
                swap(nums[left], nums[right]);
            }
        }
        return nums;
    }
};

class Solution2 {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        partition(nums.begin(), nums.end(), [](int x) { return x % 2 == 0; });
        return nums;
    }
};