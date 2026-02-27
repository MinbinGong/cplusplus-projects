/*
 * 1099. Two Sum Less Than K
 * 
 * Given an array A of integers and integer K, return the maximum S such that there exists i < j with A[i] + A[j] = S and S < K. If no i, j exist satisfying this equation, return -1.
 * 
 * 1 <= A.length <= 100
 * 1 <= A[i] <= 1000
 * 1 <= K <= 2000
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int left = 0, right = nums.size() - 1;
        int maxSum = -1;
        
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum < k) {
                maxSum = max(maxSum, sum);
                left++;
            } else {
                right--;
            }
        }
        
        return maxSum;
    }
};