/*
 * Minimum Moves to Equal Array Elements
 *
 * Given an integer array nums of size n, return the minimum number of moves required to make all array elements equal.
 *
 * In one move, you can increment n - 1 elements of the array by 1.
 *
 * Constraints:
 * n == nums.length
 * 1 <= nums.length <= 104
 * -109 <= nums[i] <= 109
 * The answer is guaranteed to fit in a 32-bit integer.
 */
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int minVal = *min_element(nums.begin(), nums.end());
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return sum - minVal * nums.size();
    }
};