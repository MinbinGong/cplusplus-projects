/*
 * 356. Line Reflection
 *
 * Given n points on a 2D plane, find if there is such a line parallel to the y-axis that reflects the given points symmetrically.
 *
 * In other words, answer whether or not if there exists a line that after reflecting all points over the given line, the original points' set is the same as the reflected ones.
 *
 * Note that there can be repeated points.
 * 
 * Example 1:
 * Input: points = [[1,1],[-1,1]]
 * Output: true
 * Explanation: We can choose the line x = 0.
 * 
 * Example 2:
 * Input: points = [[1,1],[-1,-1]]
 * Output: false
 * Explanation: We can't choose a line.
 * 
 * Constraints:
 * n == points.length
 * 1 <= n <= 104
 * -108 <= points[i][j] <= 108
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    bool isReflected(vector<vector<int>>& points) {
        if (points.empty()) return true;

        int minX = INT_MAX, maxX = INT_MIN;
        unordered_map<string, int> count;  // 键为 "x,y"

        for (auto& p : points) {
            int x = p[0], y = p[1];
            minX = min(minX, x);
            maxX = max(maxX, x);
            string key = to_string(x) + "," + to_string(y);
            count[key]++;
        }

        int sum = minX + maxX;  // 两倍的中轴线 x 坐标

        for (auto& entry : count) {
            string key = entry.first;
            int x, y;
            parseKey(key, x, y);
            int targetX = sum - x;
            string targetKey = to_string(targetX) + "," + to_string(y);

            auto it = count.find(targetKey);
            if (it == count.end()) return false;          // 对称点不存在
            if (entry.second != it->second) return false; // 出现次数不匹配
        }
        return true;
    }

private:
    void parseKey(const string& key, int& x, int& y) {
        int comma = key.find(',');
        x = stoi(key.substr(0, comma));
        y = stoi(key.substr(comma + 1));
    }
};