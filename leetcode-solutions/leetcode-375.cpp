#include <algorithm>
#include <vector>
using namespace std;

int getMoneyAmount(int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0x3f3f3f3f));
    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;

    // start iterating
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n; i++)
        {
            int j = i + l - 1;
            if (j > n)
                continue;
            dp[i][j] = min(i + dp[i + 1][j], j + dp[i][j - 1]);
            for (int k = i + 1; k < j; k++)
            {
                dp[i][j] = min(dp[i][j], max(dp[i][k - 1], dp[k + 1][j]) + k);
            }
        }
    }

    return dp[1][n];
}