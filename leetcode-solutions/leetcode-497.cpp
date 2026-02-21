/*
 * Random Point in Non-overlapping Rectangles
 *
 *  You are given an array of non-overlapping axis-aligned rectangles rects where rects[i] = [ai, bi, xi, yi] indicates that (ai, bi) is the bottom-left corner point of the ith rectangle and (xi, yi) is the top-right corner point of the ith rectangle. Design an algorithm to pick a random integer point inside the space covered by one of the given rectangles. A point on the perimeter of a rectangle is included in the space covered by the rectangle.
 *
 *  Any integer point inside the space covered by one of the given rectangles should be equally likely to be returned.
 *
 *  Note that an integer point is a point that has integer coordinates.
 *
 *  Implement the Solution class:
 *
 *  Solution(int[][] rects) Initializes the object with the given rectangles rects.
 *  int[] pick() Returns a random integer point [u, v] inside the space covered by one of the given rectangles.
 *
 *  Constraints:
 *  1 <= rects.length <= 100
 *  rects[i].length == 4
 *  -109 <= ai < xi <= 109
 *  -109 <= bi < yi <= 109
 *  xi - ai <= 2000
 *  yi - bi <= 2000
 *  All the rectangles do not overlap.
 *  At most 104 calls will be made to pick.
 * 
 */
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<vector<int>> rects;
    vector<long long> prefixSums; // prefix sum of areas
    long long totalArea;
    mt19937 gen;
    uniform_int_distribution<long long> areaDist;
    uniform_int_distribution<int> coordDist; // not used directly, we'll create per rectangle

public:
    Solution(vector<vector<int>>& rects) : rects(rects), gen(random_device{}()) {
        int n = rects.size();
        prefixSums.resize(n);
        totalArea = 0;
        for (int i = 0; i < n; ++i) {
            int x1 = rects[i][0], y1 = rects[i][1], x2 = rects[i][2], y2 = rects[i][3];
            // area = (x2 - x1 + 1) * (y2 - y1 + 1) because integer coordinates inclusive
            long long area = (long long)(x2 - x1 + 1) * (y2 - y1 + 1);
            totalArea += area;
            prefixSums[i] = totalArea;
        }
        areaDist = uniform_int_distribution<long long>(0, totalArea - 1);
    }

    vector<int> pick() {
        // Choose a random area index
        long long randArea = areaDist(gen);
        // Binary search to find the rectangle
        int idx = lower_bound(prefixSums.begin(), prefixSums.end(), randArea + 1) - prefixSums.begin();
        // Now pick a random point inside that rectangle
        const auto& rect = rects[idx];
        int x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];
        int x = uniform_int_distribution<int>(x1, x2)(gen);
        int y = uniform_int_distribution<int>(y1, y2)(gen);
        return {x, y};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */