/*
 * Minesweeper
 *
 * Let's play the minesweeper game (Wikipedia, online game)!
 * 
 * You are given a 2D char matrix representing the game board. 'M' represents an unrevealed mine, 'E' represents an unrevealed empty square, 'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines, digit ('1' to '8') represents how many mines are adjacent to this revealed square, and finally 'X' represents a revealed mine.
 * 
 * Now given the next click position (row and column indices) among all the unrevealed squares ('M' or 'E'), return the board after revealing this position according to the following rules:
 * 1. If a mine ('M') is revealed, then the game is over - change it to 'X'.
 * 2. If an empty square ('E') with no adjacent mines is revealed, then change it to revealed blank ('B') and all of its adjacent unrevealed squares should be revealed recursively.
 * 3. If an empty square ('E') with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
 * 4. Return the board when no more squares will be revealed.
 * 
 * Constraints:
 * 1 <= board.length <= 500
 * 1 <= board[i].length <= 500
 * board[i][j] is either 'M', 'E', 'B', or a digit from '1' to '8'.
 * You may assume that the click position will only ever be an unrevealed square ('M' or 'E').
 * The given board is a valid board as per the rules of Minesweeper.
 * The click position is guaranteed to be an unrevealed square.
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution1 {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int row = click[0], col = click[1];
        
        // Rule 1: Clicked on a mine
        if (board[row][col] == 'M') {
            board[row][col] = 'X';
            return board;
        }
        
        // If not a mine, start DFS from the click position
        dfs(board, row, col);
        return board;
    }

private:
    // 8 directions: top-left, top, top-right, left, right, bottom-left, bottom, bottom-right
    int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, 
                      {0, -1},           {0, 1}, 
                      {1, -1},  {1, 0},  {1, 1}};
    
    void dfs(vector<vector<char>>& board, int r, int c) {
        int rows = board.size(), cols = board[0].size();
        
        // Boundary check and ensure we only process unrevealed empty squares
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != 'E') {
            return;
        }
        
        // 1. Count adjacent mines
        int mineCount = 0;
        for (auto& dir : dirs) {
            int nr = r + dir[0], nc = c + dir[1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc] == 'M') {
                mineCount++;
            }
        }
        
        // 2. Update the current cell based on the count
        if (mineCount > 0) {
            // Rule 2: Adjacent mines exist -> change to digit
            board[r][c] = '0' + mineCount;
        } else {
            // Rule 3: No adjacent mines -> change to 'B' and recurse on neighbors
            board[r][c] = 'B';
            for (auto& dir : dirs) {
                int nr = r + dir[0], nc = c + dir[1];
                dfs(board, nr, nc);
            }
        }
    }
};

class Solution2 {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int r0 = click[0], c0 = click[1];
        int rows = board.size(), cols = board[0].size();
        
        // Rule 1: Clicked on a mine
        if (board[r0][c0] == 'M') {
            board[r0][c0] = 'X';
            return board;
        }
        
        // 8 directions
        int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, 
                          {0, -1},           {0, 1}, 
                          {1, -1},  {1, 0},  {1, 1}};
        
        queue<pair<int, int>> q;
        q.push({r0, c0});
        
        // Mark as visited to avoid re-processing. We'll change it to its final value later.
        // A common trick is to set it to a temporary marker, e.g., '0' for 'Being Processed'.
        board[r0][c0] = '0'; 
        
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            
            // Count adjacent mines
            int mineCount = 0;
            vector<pair<int, int>> neighbors; // Store potential neighbors for later processing
            for (auto& dir : dirs) {
                int nr = r + dir[0], nc = c + dir[1];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                    if (board[nr][nc] == 'M') {
                        mineCount++;
                    } else if (board[nr][nc] == 'E') {
                        neighbors.push_back({nr, nc});
                    }
                }
            }
            
            // Update the current cell's final value
            if (mineCount > 0) {
                board[r][c] = '0' + mineCount;
            } else {
                board[r][c] = 'B';
                // Rule 3: Add all adjacent 'E' squares to the queue for processing
                for (auto& [nr, nc] : neighbors) {
                    if (board[nr][nc] == 'E') {
                        board[nr][nc] = '0'; // Mark as visited before pushing to queue
                        q.push({nr, nc});
                    }
                }
            }
        }
        return board;
    }
};