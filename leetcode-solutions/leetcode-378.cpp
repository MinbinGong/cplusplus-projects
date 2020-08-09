#include <vector>
using namespace std;

int check(int mid, vector<vector<int>> &matrix)
{
    int y = matrix[0].size() - 1;
    int x = 0;
    int lower = 0;
    while (true)
    {
        if (matrix[x][y] > mid)
        {
            if (y != 0)
            {
                --y;
            }
            else
            {
                return lower;
            }
        }
        else
        {
            if (x != matrix.size() - 1)
            {
                lower += (y + 1);
                x++;
            }
            else
            {
                lower += (y + 1);
                return lower;
            }
        }
    }
    return lower;
}

int kthSmallest(vector<vector<int>> &matrix, int k)
{
    int low = matrix[0][0];
    int high = matrix[matrix.size() - 1][matrix[0].size() - 1];

    int res = -1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int lower = check(mid, matrix);
        if (lower < k)
        {
            low = mid + 1;
        }
        else
        {
            res = mid;
            high = mid - 1;
        }
    }
    return res;
}
