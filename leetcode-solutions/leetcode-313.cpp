#include <vector>
#include <algorithm>
using namespace std;

int nthSuperUglyNumber(int n, vector<int> &primes)
{
    vector<int> cpr(primes.begin(), primes.end());
    vector<int> ind(primes.size(), 0);
    vector<long long> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i < n; ++i)
    {
        long long int m = 1e18;
        for (auto p : primes)
        {
            m = min(m, (long long)p);
        }
        dp[i] = m;
        for (int j = 0; j < primes.size(); j++)
        {
            if (m == primes[j])
            {
                ind[j]++;
                primes[j] = dp[ind[j]] * cpr[j];
            }
        }
    }
    return dp[n - 1];
}