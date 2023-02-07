#include <vector>

bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target)
{
    if (matrix.size() == 0 || matrix.size() == 0)
    {
        return false;
    }

    int i = 0, j = matrix[0].size() - 1;
    while (i < matrix.size() && j >= 0)
    {
        int x = matrix[i][j];
        if (target == x)
        {
            return true;
        }
        else if (x < target)
        {
            ++i;
        }
        else
        {
            --j;
        }
    }
    return false;
}