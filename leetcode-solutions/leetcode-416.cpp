#include <vector>
#include <numeric>
bool canPartition(std::vector<int> &nums)
{
    unsigned long long int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0)
        return false;
    unsigned long long int size = sum / 2;
    std::vector<unsigned long long int> dp(size + 1, 0);
    dp[0] = 1;
    for (size_t i = 1; i < nums.size(); i++)
    {
        for (size_t j = size; j >= nums[i]; --j)
        {
            dp[j] += dp[j - nums[i]];
        }
    }
    return dp[size];
}