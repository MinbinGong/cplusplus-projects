#include <vector>

bool dfs(const std::vector<std::vector<int>>& maze, const std::vector<int>& destination,
    const std::vector<int>& pos, std::vector<std::vector<bool>>& visited)
{
    if (destination == pos)
    {
        return true;
    }

    if (visited[pos[0]][pos[1]])
    {
        return false;
    }
    visited[pos[0]][pos[1]] = true;

    unsigned int m = maze.size();
    unsigned int n = maze[0].size();

    std::vector<std::vector<int>> directions = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    for (const auto& direction : directions)
    {
        int i = direction[0], j = direction[1];
        std::vector<int> newPos(pos);
        while (0 <= newPos[0] + i && newPos[0] + i < m && 0 <= newPos[1] + j && newPos[1] + j < n &&
            maze[newPos[0] + i][newPos[1] + j] != 1)
        {
            newPos[0] += i;
            newPos[1] += j;
        }

        if (dfs(maze, destination, newPos, visited)
        {
            return true;
        }
    }
    return false;
}

bool hasPath(std::vector<std::vector<int>>& maze, std::vector<int>& start, std::vector<int>& dest)
{
    unsigned int m = maze.size();
    unsigned int n = maze[0].size();
    std::vector<std::vector<bool>> visited(m, std::vector<boo>(n));
    return dfs(maze, dest, start, visited);
}