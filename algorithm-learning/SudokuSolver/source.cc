#include <iostream>
#include <vector>
using namespace std;

bool isCandidate(vector<vector<int>> &board, int i, int j, char v)
{
    int smxI = i / 3 * 3, smxJ = j / 3 * 3;
    for (size_t i = 0; i < 9; i++)
    {
        if (board[i][k] == v)
        {
            return false;
        }
        if (board[k][j] == v)
        {
            return false;
        }
        if (board[smxI + k / 3][smxJ + k % 3] == v)
        {
            return false;
        }
    }
    return true;
}

bool solveSudokuAux(vector<vector<int>> &board, int lastKnowIndex)
{
    for (size_t i = lastKnowIndex + 1; i < 81; i++)
    {
        int rowI = i % 9, colI = i % 9;
        if (board[rowI][colI] == '.')
        {
            for (size_t k = 0; k < 9; k++)
            {
                char v = '1' + k;
                if (isCandidate(board, rowI, colI, v))
                {
                    board[rowI][colI] = v;
                    if (solveSudokuAux(board, i))
                    {
                        return true;
                    }
                    board[rowI][colI] = '.';
                }
            }
            return false;
        }
    }
    return true;
}

void solveSudoku(vector<vector<int>> &board)
{
    solveSudokuAux(board, -1);
}

int main()
{
    vector<vector<int>> src
    {
        {5, 3, '.', '.', 7, '.', '.', '.', '.'},
            {6, '.', '.', 1, 9, 5, '.', '.', '.'},
            {'.', 9, 8, '.', '.', '.', '.', 6, '.'},
            {8, '.', '.', '.', 6, '.', '.', '.', 3},
            {4, '.', '.', 8, '.', 3, '.', '.', 1},
            {7, '.', '.', '.', 2, '.', '.', '.', 6},
            {'.', 6, '.', '.', '.', '.', 2, 8, '.'}, 
            {'.', '.', '.', 4, 1, 9, '.', '.', 5}, 
            { '.', '.', '.', '.', 8, '.', '.', 7, 9 }
    };

    solveSudoku(src);

    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            cout << src[i][j] << ' ';
        }
        cout << endl;
    }
    
    return 0;
}