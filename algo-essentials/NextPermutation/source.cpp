#include <vector>
#include <algorithm>

bool next_permutation(std::vector<int>& nums, int begin, int end)
{
    int p = end - 1;
    while (p >= 0 && nums[p] >= nums[p+1])
    {
        --p;
    }

    if (p == -1)
    {
        std::reverse(nums.begin(), nums.end());
        return false;
    }

    int c = end - 1;
    while (c>0&& nums[c]<=nums[p])
    {
        --c;
    }

    std::swap(nums[p], nums[c]);
    std::reverse(&nums[p + 1], &nums[end]);
    return true;
}

void nextPermutation(std::vector<int>& nums)
{
    next_permutation(nums, 0, nums.size());
}