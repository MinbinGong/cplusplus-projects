#include <vector>
using namespace std;

int islandPerimeter(vector<vector<int>> &grid)
{
    int res = grid[0][0] ? 4 : 0;

    for (int j = 1; j < grid[0].size(); ++j)
        if (grid[0][j])
        {
            if (grid[0][j - 1])
                res += 2;
            else
                res += 4;
        }

    for (int i = 1; i < grid.size(); ++i)
        if (!grid[i][0])
            continue;
        else if (grid[i - 1][0])
            res += 2;
        else
            res += 4;

    for (int i = 1; i < grid.size(); ++i)
    {
        for (int j = 1; j < grid[0].size(); ++j)
        {
            if (!grid[i][j])
                continue;
            else if (grid[i][j - 1] && grid[i - 1][j])
                ;
            else if (grid[i][j - 1] || grid[i - 1][j])
                res += 2;
            else
                res += 4;
        }
    }
    return res;
}