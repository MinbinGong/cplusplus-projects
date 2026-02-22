/*
 * Lonely Pixel II
 * 
 * Given a picture consisting of black and white pixels, and a positive integer N, find the number of black pixels located at some specific row R and column C that align with all the following rules:
 * 1. Row R and column C both contain exactly N black pixels.
 * 2. For all rows that have a black pixel at column C, they should be exactly the same as row R
 * 
 * The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.
 * 
 * Example:
 * Input: 
 * [['W', 'B', 'W', 'B', 'B', 'W'],
 *  ['W', 'B', 'W', 'B', 'B', 'W'],
 *  ['W', 'B', 'W', 'B', 'B', 'W'],
 *  ['W', 'W', 'B', 'W', 'B', 'W']] 
 * 
 * N = 3
 * Output: 6
 * 
 * Explanation: All the bold 'B' are the black pixels we need (all 'B's at column 1 and 3).
 *         0    1    2    3    4    5         column index
 * 0    [['W', 'B', 'W', 'B', 'B', 'W'],
 * 1     ['W', 'B', 'W', 'B', 'B', 'W'],
 * 2     ['W', 'B', 'W', 'B', 'B', 'W'],
 * 3     ['W', 'W', 'B', 'W', 'B', 'W']]
 * row index
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findBlackPixel(vector<vector<char>>& picture, int N) {
        int m = picture.size();
        if (m == 0) return 0;
        int n = picture[0].size();

        vector<int> rowCount(m, 0);
        vector<int> colCount(n, 0);
        unordered_map<string, int> rowStrCount; // 统计每种行字符串出现的次数
        vector<string> rowStrs(m);              // 存储每一行的字符串形式

        // 1. 第一次遍历：统计行列的B的数量，并记录行字符串
        for (int i = 0; i < m; ++i) {
            string rowStr = "";
            for (int j = 0; j < n; ++j) {
                rowStr += picture[i][j];
                if (picture[i][j] == 'B') {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
            rowStrs[i] = rowStr;
            rowStrCount[rowStr]++;
        }

        // 2. 第二次遍历：找出符合条件的 'B'
        int lonelyPixelCount = 0;
        for (int i = 0; i < m; ++i) {
            // 如果当前行的B的数量不是N，或者当前行字符串出现的次数不是N，那么这一行不可能有孤独像素
            if (rowCount[i] != N || rowStrCount[rowStrs[i]] != N) {
                continue;
            }
            for (int j = 0; j < n; ++j) {
                // 如果当前位置是B，并且该列的B的数量也恰好是N
                if (picture[i][j] == 'B' && colCount[j] == N) {
                    lonelyPixelCount++;
                }
            }
        }
        return lonelyPixelCount;
    }
};