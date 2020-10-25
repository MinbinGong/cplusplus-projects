#include <vector>
#include <algorithm>
using namespace std;

int minMove2(vector<int> &nums)
{
    int ans{0};

    sort(nums.begin(), nums.end());

    int x = nums[nums.size() / 2];
    for (int num : nums)
    {
        ans += abs(x - num);
    }

    return ans;
}