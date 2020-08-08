#include <vector>
using namespace std;

int wiggleMaxLength(vector<int> &nums)
{
    int len = nums.size();
    if (len == 0 || len == 1)
        return len;

    // vector<int> copy=nums;
    vector<bool> dp;
    for (int i = 0; i < len - 1; i++)
    {
        int diff = nums[i] - nums[i + 1];
        if (diff == 0)
            continue;
        else
        {
            if (diff < 0)
                dp.push_back(false);
            else
                dp.push_back(true);
        }
    }

    if (dp.size() == 0 || dp.size() == 1)
        return 1;

    int count = 1;
    bool cur = dp[0];
    for (int i = 1; i < dp.size(); i++)
    {
        if (dp[i] == !cur)
        {
            count++;
            cur = !cur;
        }
    }
    return count + 1;
}
