#include <queue>
#include <vector>
#include <algorithm>

int maxSlidingWindow(std::vector<int>& nums, int k)
{
    std::vector<int> res(nums.size() - k + 1);
    std::deque<int> q;

    for (size_t i = 0, j = 0; i < nums.size(); i++)
    {
        if (!q.empty() && q.front() == i-k)
        {
            q.pop_front();
        }

        while (!q.empty() && nums[q.back()] < nums[i])
        {
            q.pop_back();
        }

        q.push_back(i);
        if (i >= k-1)
        {
            res[j++] = nums[q.front()];
        }
    }

    return std::max_element(res.begin(), res.end());
}