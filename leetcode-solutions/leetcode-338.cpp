#include <vector>
using namespace std;

vector<int> countBits(int num)
{
    if (num == 0)
        return {0};
    vector<int> dp(num + 1, 0);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= num; i++)
    {
        if (i & 1)
            dp[i] = dp[i >> 1] + 1; // i&1 is bitwise AND which is used to check whether last bit is 1 or not.
        else
            dp[i] = dp[i >> 1];
    }
    return dp;
}