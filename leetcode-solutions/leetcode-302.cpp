/*
 * Smallest Rectangle Enclosing Black Pixels
 * 
 * An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel.
 * The black pixels are connected, i.e., there is only one black region. Pixels are connected
 * horizontally and vertically. Given the location (x, y) of one of the black pixels, return
 * the area of the smallest (axis-aligned) rectangle that encloses all black pixels.
 * 
 * Example:
 * Input:
 * [
 *   "0010",
 *   "0110",
 *   "0100"
 * ]
 * and x = 0, y = 2
 * 
 * Output: 6
 * 
 */
#include <vector>
using namespace std;

// 题目要求的是最小的矩形，所以我们需要找到所有黑色像素的最小和最大的行号和列号。
class Solution1 {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        int m = image.size(), n = image[0].size();
        int minRow = m, maxRow = 0, minCol = n, maxCol = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (image[i][j] == '1') {
                    minRow = min(minRow, i);
                    maxRow = max(maxRow, i);
                    minCol = min(minCol, j);
                    maxCol = max(maxCol, j);
                }
            }
        }
        return (maxRow - minRow + 1) * (maxCol - minCol + 1);
    }
};

class Solution2 {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        int m = image.size(), n = image[0].size();
        int minRow = m, maxRow = 0, minCol = n, maxCol = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        dfs(image, x, y, minRow, maxRow, minCol, maxCol, visited);
        return (maxRow - minRow + 1) * (maxCol - minCol + 1);
    }

private:
    void dfs(vector<vector<char>>& image, int i, int j, int &minRow, int &maxRow,
             int &minCol, int &maxCol, vector<vector<bool>>& visited) {
        int m = image.size(), n = image[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || image[i][j] != '1') return;

        visited[i][j] = true;
        minRow = min(minRow, i);
        maxRow = max(maxRow, i);
        minCol = min(minCol, j);
        maxCol = max(maxCol, j);

        dfs(image, i + 1, j, minRow, maxRow, minCol, maxCol, visited);
        dfs(image, i - 1, j, minRow, maxRow, minCol, maxCol, visited);
        dfs(image, i, j + 1, minRow, maxRow, minCol, maxCol, visited);
        dfs(image, i, j - 1, minRow, maxRow, minCol, maxCol, visited);
    }
};

class Solution3 {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        int m = image.size(), n = image[0].size();
        int top = searchTop(image, 0, x, 0, n);
        int bottom = searchBottom(image, x, m - 1, 0, n);
        int left = searchLeft(image, 0, y, top, bottom);
        int right = searchRight(image, y, n - 1, top, bottom);
        return (bottom - top + 1) * (right - left + 1);
    }

private:
    // 在 [startRow, endRow] 范围内找第一个有黑色像素的行
    int searchTop(vector<vector<char>>& image, int startRow, int endRow, int l, int r) {
        while (startRow < endRow) {
            int mid = startRow + (endRow - startRow) / 2;
            if (hasBlackInRow(image, mid, l, r)) {
                endRow = mid;
            } else {
                startRow = mid + 1;
            }
        }
        return startRow;
    }

    // 在 [startRow, endRow] 范围内找最后一个有黑色像素的行
    int searchBottom(vector<vector<char>>& image, int startRow, int endRow, int l, int r) {
        while (startRow < endRow) {
            int mid = startRow + (endRow - startRow + 1) / 2;
            if (hasBlackInRow(image, mid, l, r)) {
                startRow = mid;
            } else {
                endRow = mid - 1;
            }
        }
        return startRow;
    }

    // 在 [startCol, endCol] 范围内找第一个有黑色像素的列
    int searchLeft(vector<vector<char>>& image, int startCol, int endCol, int t, int b) {
        while (startCol < endCol) {
            int mid = startCol + (endCol - startCol) / 2;
            if (hasBlackInCol(image, mid, t, b)) {
                endCol = mid;
            } else {
                startCol = mid + 1;
            }
        }
        return startCol;
    }

    // 在 [startCol, endCol] 范围内找最后一个有黑色像素的列
    int searchRight(vector<vector<char>>& image, int startCol, int endCol, int t, int b) {
        while (startCol < endCol) {
            int mid = startCol + (endCol - startCol + 1) / 2;
            if (hasBlackInCol(image, mid, t, b)) {
                startCol = mid;
            } else {
                endCol = mid - 1;
            }
        }
        return startCol;
    }

    // 判断第 r 行在列区间 [l, r] 内是否有黑色像素
    bool hasBlackInRow(vector<vector<char>>& image, int r, int l, int rCol) {
        for (int j = l; j < rCol; ++j) {
            if (image[r][j] == '1') return true;
        }
        return false;
    }

    // 判断第 c 列在行区间 [t, b] 内是否有黑色像素
    bool hasBlackInCol(vector<vector<char>>& image, int c, int t, int b) {
        for (int i = t; i <= b; ++i) {
            if (image[i][c] == '1') return true;
        }
        return false;
    }
};