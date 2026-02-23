/*
 * Flood Fill
 *
 * An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65535).
 * 
 * Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.
 * 
 * To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel), and so on. Replace the color of all of the aforementioned pixels with the newColor.
 * 
 * At the end, return the modified image.
 * 
 * Note:
 * 1. The length of image and image[0] will be in the range [1, 50].
 * 2. The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
 * 3. The value of each color in image[i][j] and newColor will be an integer in [0, 65535].
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int oldColor = image[sr][sc];
        if (oldColor == newColor) return image; // no change needed
        dfs(image, sr, sc, oldColor, newColor);
        return image;
    }

private:
    void dfs(vector<vector<int>>& image, int r, int c, int oldColor, int newColor) {
        // Check boundaries and if the current pixel matches the old color
        if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size() || image[r][c] != oldColor)
            return;

        image[r][c] = newColor; // fill with new color

        // Recursively visit neighbors (4‑direction)
        dfs(image, r + 1, c, oldColor, newColor);
        dfs(image, r - 1, c, oldColor, newColor);
        dfs(image, r, c + 1, oldColor, newColor);
        dfs(image, r, c - 1, oldColor, newColor);
    }
};
