/*
 * Given a non-empty array of integers nums, every element appears twice except for one. 
 * Find that single one.
 */
#include <vector>
using namespace std;

int findSingleNumber(vector<int> &nums)
{
    int ret = nums[0];
    for (size_t i = 1; i < nums.size(); ++i)
    {
        ret ^= nums[i];
    }
    return ret;
}