#include <vector>

int dfs(std::vector<std::vector<int>> res, int x, int y)
{
    if (x < 0 || y < 0)
    {
        return 0;
    }

    if (x == 0 && y == 0)
    {
        return res[0][0];
    }

    if (res[x][y] > 0)
    {
        return res[x][y];
    }
    else
    {
        return res[x][y] + dfs(x - 1, y) + dfs(x, y - 1);
    }
}

int unique_paths(int m, int n)
{
    std::vector<std::vector<int>> res = std::vector<int>(m, std::vector<int>(n, 0));
    res[0][0] = 1;

    return dfs(m - 1, n - 1);
}