/*
 * Lonely Pixel I
 *
 * Given a picture consisting of black and white pixels, find the number of black lonely pixels.
 * 
 * A black lonely pixel is character 'B' that located at a specific position where the same row and same column don't have any other black pixels.
 * 
 * Example:
 * Input: 
 * [['W', 'W', 'B'],
 *  ['W', 'B', 'W'],
 *  ['B', 'W', 'W']]
 * Output: 3
 * Explanation: All the three 'B's are black lonely pixels.
 * 
 * Note:
 * The range of width and height of the input 2D array is [1,500].
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        int m = picture.size();
        if (m == 0) return 0;
        int n = picture[0].size();

        // 1. 第一次遍历：统计每行和每列的 'B' 数量
        vector<int> rowCount(m, 0);
        vector<int> colCount(n, 0);
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (picture[i][j] == 'B') {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }

        // 2. 第二次遍历：找出符合条件的 'B'
        int lonelyPixelCount = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (picture[i][j] == 'B' && rowCount[i] == 1 && colCount[j] == 1) {
                    lonelyPixelCount++;
                }
            }
        }
        
        return lonelyPixelCount;
    }
};