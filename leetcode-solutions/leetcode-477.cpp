/*
 * Total Hamming Distance
 *
 * The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
 * 
 * Given an integer array nums, return the sum of Hamming distances between all the pairs of the integers in nums.
 * 
 * Constraints:
 * 1 <= nums.length <= 104
 * 0 <= nums[i] <= 109
 * The answer for the given input will fit in a 32-bit integer.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size();
        long long total = 0;
        for (int bit = 0; bit < 32; ++bit) {
            int countOne = 0;
            for (int num : nums) {
                if (num >> bit & 1) {
                    ++countOne;
                }
            }
            total += (long long)countOne * (n - countOne);
        }
        return total;
    }
};