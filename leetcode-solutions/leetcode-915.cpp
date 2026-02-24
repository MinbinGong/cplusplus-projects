/*
 * Partition Array into Disjoint Intervals
 *
 * Given an array A, partition it into two (contiguous) subarrays left and right so that:
 * 
 * Every element in left is less than or equal to every element in right.
 * left and right are non-empty.
 * left has the smallest possible size.
 * Return the length of left after such a partitioning.  It is guaranteed that such a partitioning exists.
 * 
 * Example 1:
 * Input: [5,0,3,8,6]
 * Output: 3
 * Explanation: left = [5,0,3], right = [8,6]
 * 
 * Note:
 * 2 <= A.length <= 30000
 * 0 <= A[i] <= 10^6
 * It is guaranteed there is at least one way to partition A as described.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size();
        // leftMax[i] = maximum in nums[0..i]
        vector<int> leftMax(n);
        leftMax[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            leftMax[i] = max(leftMax[i-1], nums[i]);
        }

        // rightMin[i] = minimum in nums[i..n-1]
        vector<int> rightMin(n);
        rightMin[n-1] = nums[n-1];
        for (int i = n-2; i >= 0; --i) {
            rightMin[i] = min(rightMin[i+1], nums[i]);
        }

        // Find the smallest left part length such that max(left) <= min(right)
        for (int i = 0; i < n-1; ++i) {
            if (leftMax[i] <= rightMin[i+1]) {
                return i + 1;
            }
        }
        // According to the problem, an answer always exists.
        return -1;
    }
};