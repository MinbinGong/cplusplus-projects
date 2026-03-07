/**
 * 1620. Coordinate With Maximum Network Quality
 * 
 * You are given an array of network towers towers, where towers[i] = [xi, yi, qi] denotes the ith network tower with location (xi, yi) and quality factor qi. All the coordinates are integral coordinates on the X-Y plane, and the distance between the two coordinates is the Euclidean distance.
 * 
 * You are also given an integer radius where a tower is reachable if the distance is less than or equal to radius. Outside that distance, the signal becomes garbled, and the tower is not reachable.
 * 
 * The signal quality of the ith tower at a coordinate (x, y) is calculated with the formula ⌊qi / (1 + d)⌋, where d is the distance between the tower and the coordinate. The network quality at a coordinate is the sum of the signal qualities from all the reachable towers.
 * 
 * Return the array [cx, cy] representing the integral coordinate (cx, cy) where the network quality is maximum. If there are multiple coordinates with the same network quality, return the lexicographically minimum non-negative coordinate.
 * 
 * Example 1:
 * Input: towers = [[1,2,5],[2,1,7],[3,1,9]], radius = 2
 * Output: [2,1]
 * Explanation: 
 * At coordinate (2, 1) the network quality is 13.
 * 
 * Example 2:
 * Input: towers = [[23,11,21]], radius = 9
 * Output: [23,11]
 * Explanation: 
 * At coordinate (23, 11) the network quality is 7.
 * 
 * Example 3:
 * Input: towers = [[1,2,13],[2,1,7],[0,1,9]], radius = 2
 * Output: [1,2]
 * Explanation: 
 * At coordinate (1, 2) the network quality is 7.
 * 
 * Constraints:
 * 1 <= towers.length <= 50
 * towers[i].length == 3
 * 0 <= xi, yi, qi <= 50
 * 1 <= radius <= 50
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        int maxQuality = -1;
        vector<int> ans = {0, 0}; // 默认值

        // 坐标范围是 0 到 50
        for (int x = 0; x <= 50; ++x) {
            for (int y = 0; y <= 50; ++y) {
                int quality = 0;
                for (const auto& tower : towers) {
                    int tx = tower[0], ty = tower[1], q = tower[2];
                    double d = sqrt((x - tx) * (x - tx) + (y - ty) * (y - ty));
                    if (d <= radius) {
                        quality += static_cast<int>(q / (1 + d));
                    }
                }
                // 比较并更新答案
                if (quality > maxQuality) {
                    maxQuality = quality;
                    ans = {x, y};
                } else if (quality == maxQuality) {
                    if (x < ans[0] || (x == ans[0] && y < ans[1])) {
                        ans = {x, y};
                    }
                }
            }
        }
        return ans;
    }
};