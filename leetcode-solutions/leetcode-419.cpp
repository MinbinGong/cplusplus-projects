#include <vector>
using namespace std;

int countBattleships(vector<vector<char>> &board)
{
    int count = 0;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == 'X')
            {
                if (i - 1 >= 0 and board[i - 1][j] == 'X')
                    continue;

                if (j - 1 >= 0 and board[i][j - 1] == 'X')
                    continue;

                count++;
            }
        }
    }

    return count;
}
