#include <vector>
#include <unordered_map>
using namespace std;

int numberOfArithmethicsSlices(vector<int> &A)
{
    int res = 0;
    unordered_map<int, vector<int>> a_idx;
    vector<vector<int>> dp(A.size(), vector<int>(A.size()));
    for (size_t i = 0; i < A.size(); i++)
    {
        a_idx[A[i]].push_back(i);
    }

    for (size_t i = 0; i < A.size(); i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            auto prev = 2l * A[j] - A[i];
            if (prev < INT_MIN || prev > INT_MAX)
            {
                continue;
            }
            auto it = a_idx.find(prev);
            if (it != a_idx.end())
            {
                for (auto k : it->second)
                {
                    if (k >= j)
                    {
                        break;
                    }
                    dp[i][j] += dp[j][k] + 1;
                }
            }
            res += dp[i][j];
        }
    }
    return res;
}