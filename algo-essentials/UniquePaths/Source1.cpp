#include <vector>

int unique_path(int m, int n)
{
    std::vector<int> f(n, 0);
    f[0] = 1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            f[j] += f[j - 1];
        }
    }

    return f[n - 1];
}