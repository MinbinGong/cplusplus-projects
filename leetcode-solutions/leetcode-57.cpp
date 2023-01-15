// You are given an array of non - overlapping intervals intervals where intervals[i] = [ starti, endi ]
// represent the start and the end of the ith interval and intervals is sorted in ascending order by starti.
// You are also given an interval newInterval = [ start, end ] that represents the start and end of another interval.
// Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and
// intervals still does not have any overlapping intervals(merge overlapping intervals if necessary).
// Return intervals after the insertion.

#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> insert(vector<vector<int>> &nums, vector<int> &new_nums)
{
    int n = nums.size();
    if (0 == n)
    {
        return {new_nums};
    }

    bool flag{false};
    for (int i = 0; i < n; i++)
    {
        if (new_nums[0] < nums[i][0] && new_nums[1] < nums[i][0])
        {
            nums.insert(nums.begin() + i, new_nums);
            flag = true;
            break;
        }

        if (nums[i][0] <= new_nums[0] && new_nums[0] <= nums[i][1] || new_nums[0] <= nums[i][0])
        {
            int start = i, end = i;
            while (i < n && new_nums[1] >= nums[i][0])
            {
                end = i;
                i++;
            }

            new_nums[0] = min(nums[start][0], new_nums[0]);
            new_nums[1] = max(nums[end][1], new_nums[1]);
            nums.erase(nums.begin() + start, nums.begin() + i);
            nums.insert(nums.begin() + start, new_nums);
            flag = true;
            break;
        }
    }

    if (false == flag)
    {
        nums.push_back(new_nums);
    }
    return nums;
}