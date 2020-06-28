#include <vector>
#include <algorithm>
using namespace std;

int maxProfit(vector<int> &prices)
{
    int n = prices.size();
    if (n <= 1)
        return 0;

    int buy{0}, sell{1};
    int dp[3][2];

    for (int i = 1; i < n; i++)
    {
        dp[2][sell] = max(dp[1][sell], dp[1][buy] + prices[i]);
        dp[2][buy] = -prices[i];

        if (i >= 2)
        {
            dp[2][buy] += dp[0][sell];
        }
        dp[2][buy] = max(dp[2][buy], dp[1][buy]);

        for (int k = 0; k < 2; k++)
        {
            dp[0][k] = dp[1][k];
            dp[1][k] = dp[2][k];
        }
    }

    return dp[2][sell];
}