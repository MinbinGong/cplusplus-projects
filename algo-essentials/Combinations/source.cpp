#include <vector>

void dfs(int n, int k, int start, int cur, std::vector<int>& path, std::vector<std::vector<int>>& res)
{
    if (cur == k)
    {
        res.push_back(path);
        return;
    }

    for (int i = start; i <= n; i++)
    {
        path.push_back(i);
        dfs(n, k, i + 1, cur + 1, path, res);
        path.pop_back();
    }
}

std::vector<std::vector<int>> combine(int n, int k)
{
    std::vector<std::vector<int>> res;
    std::vector<int> path;
    dfs(n, k, 1, 0, path, res);
    return res;
}