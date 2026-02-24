/*
 * Sort Array By Parity II
 *
 * Given an array A of non-negative integers, half of the integers in A are odd, and half of the integers are even.
 *
 * Sort the array so that whenever A[i] is odd, i is odd; and whenever A[i] is even, i is even.
 *
 * You may return any answer array that satisfies this condition.
 *
 * Example 1:
 * Input: [4,2,5,7]
 * Output: [4,5,2,7]
 * Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
 *
 * Note:
 * 2 <= A.length <= 20000
 * A.length % 2 == 0
 * 0 <= A[i] <= 1000
 *
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int n = nums.size();
        int even = 0;  // even index
        int odd = 1;   // odd index
        
        while (even < n && odd < n) {
            // find first even index with an odd number
            while (even < n && nums[even] % 2 == 0) {
                even += 2;
            }
            // find first odd index with an even number
            while (odd < n && nums[odd] % 2 == 1) {
                odd += 2;
            }
            // swap them
            if (even < n && odd < n) {
                swap(nums[even], nums[odd]);
            }
        }
        return nums;
    }
};