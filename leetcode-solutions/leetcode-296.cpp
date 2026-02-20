/*
 * Best Meeting Point
 *
 * A group of two or more people wants to meet and minimize the total travel distance.
 * You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group.
 * The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.
 * 
 * Example:
 * 
 * Input: 
 * 
 * 1 - 0 - 0 - 0 - 1
 * |   |   |   |   |
 * 0 - 0 - 0 - 0 - 0
 * |   |   |   |   |
 * 0 - 0 - 1 - 0 - 0
 * 
 * Output: 6 
 * 
 * Explanation: Given three people living at (0,0), (0,4), and (2,2):
 *              The point (0,2) is an ideal meeting point, as the total travel distance 
 *              of 2+2+2=6 is minimal. So return 6.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        vector<int> rows, cols;
        int m = grid.size(), n = grid[0].size();
        
        // 收集所有 1 的行坐标
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    rows.push_back(i);
                }
            }
        }
        // 收集所有 1 的列坐标（注意遍历顺序）
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                if (grid[i][j] == 1) {
                    cols.push_back(j);
                }
            }
        }
        
        // 计算到中位数的距离之和
        return getMinDist(rows) + getMinDist(cols);
    }
    
private:
    int getMinDist(vector<int>& points) {
        sort(points.begin(), points.end());
        int median = points[points.size() / 2];
        int total = 0;
        for (int p : points) {
            total += abs(p - median);
        }
        return total;
    }
};

class Solution2 {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> rows, cols;
        
        // 收集行坐标（行已经按顺序收集）
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) rows.push_back(i);
            }
        }
        // 收集列坐标
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                if (grid[i][j] == 1) cols.push_back(j);
            }
        }
        
        // 列坐标需要排序（行坐标已经有序）
        sort(cols.begin(), cols.end());
        
        // 双指针计算距离和
        return getDist(rows) + getDist(cols);
    }
    
private:
    int getDist(vector<int>& points) {
        int i = 0, j = points.size() - 1;
        int res = 0;
        while (i < j) {
            res += points[j--] - points[i++];
        }
        return res;
    }
};