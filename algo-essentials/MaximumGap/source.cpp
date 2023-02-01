#include <climits>
#include <cmath>
#include <vector>

int maximumGap(std::vector<int>& nums)
{
    if (nums.size() < 2)
    {
        return 0;
    }
    
    int mini = INT_MAX, maxi = INT_MIN;
    int sz = nums.size();
    for (size_t i = 0; i < sz; i++)
    {
        mini = mini < nums[i] ? mini : nums[i];
        maxi = maxi > nums[i] ? maxi : nums[i];
    }

    int gap = std::ceil((max - min) / ((sz - 1) * 1.0));
    if (gap == 0)
    {
        return 0;
    }

    std::vector<int> bucket_max(sz, INT_MIN), bucket_min(sz, INT_MAX);
    for (size_t i = 0; i < sz; i++)
    {
        int index = (nums[i] - mini) / gap;
        bucket_min[index] = bucket_min[index] < nums[i] ? bucket_min[i] : nums[i];
        bucket_max[index] = bucket_max[index] > nums[i] ? bucket_max[i] : nums[i];
    }

    int prev = mini, ans = 0;
    for (size_t i = 0; i < bucket_min.size(); i++)
    {
        if (bucket_max[i] != INT_MIN)
        {
            ans = ans > bucket_min[i] ? ans : bucket_min[i];
            prev = bucket_max[i];
        }
    }

    ans = ans > (maxi - prev) ? ans : (maxi - prev);

    return 0;
}