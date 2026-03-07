/**
 * 1610. Maximum Number of Visible Points
 * 
 * You are given an array points, an integer angle, and your location, where location = [posx, posy] and points[i] = [xi, yi] both denote integral coordinates on the X-Y plane.
 * 
 * Initially, you are facing directly east from your position. You cannot move from your position, but you can rotate. In other words, posx and posy cannot be changed. Your field of view in degrees is represented by angle, determining how wide you can see from any given view direction. Let d be the amount in degrees that you rotate counterclockwise. Then, your field of view is the inclusive range of angles [d - angle/2, d + angle/2].
 * 
 * You can see some set of points if, for each point, the angle formed by the point, your position, and the immediate east direction from your position is in your field of view.
 * 
 * There can be multiple points at one coordinate. There may be points at your location, and you can always see these points regardless of your rotation. Points do not obstruct your vision to other points.
 * 
 * Example 1:
 * Input: points = [[2,1],[2,2],[3,3]], angle = 90, location = [1,1]
 * Output: 3
 * Explanation: The shaded region represents your field of view. All points can be made visible in your field of view, including [3,3] even though [2,2] is in front and in the same line of sight.
 * 
 * Example 2:
 * Input: points = [[2,1],[2,2],[3,4],[1,1]], angle = 90, location = [1,1]
 * Output: 4
 * Explanation: All points can be made visible in your field of view, including the one at your location.
 * 
 * Example 3:
 * Input: points = [[1,0],[2,1]], angle = 13, location = [1,1]
 * Output: 1
 * Explanation: You can only see one of the two points, as shown above.
 * 
 * Constraints:
 * 1 <= points.length <= 105
 * points[i].length == 2
 * location.length == 2
 * 0 <= angle < 360
 * 0 <= posx, posy, xi, yi <= 100
 * 
 * Follow up: Could you solve it both recursively and iteratively?
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        const double PI = acos(-1.0);
        const double ANGLE_RAD = angle * PI / 180.0;   // 将角度转为弧度
        const double EPS = 1e-8;                       // 浮点精度容差
        
        int selfCount = 0;                              // 与 location 重合的点数
        vector<double> ang;                              // 存储所有非重合点的极角
        
        // 1. 计算每个点相对于 location 的极角
        for (const auto& p : points) {
            int dx = p[0] - location[0];
            int dy = p[1] - location[1];
            
            if (dx == 0 && dy == 0) {
                // 与观测点重合，无论怎样旋转都能看见
                selfCount++;
            } else {
                // atan2(dy, dx) 返回值范围 [-π, π]
                double a = atan2(dy, dx);
                ang.push_back(a);
            }
        }
        
        // 2. 排序极角
        sort(ang.begin(), ang.end());
        int n = ang.size();
        
        // 3. 处理环形：将每个角度加上 2π 后追加到末尾
        for (int i = 0; i < n; i++) {
            ang.push_back(ang[i] + 2 * PI);
        }
        
        // 4. 滑动窗口寻找能覆盖最多点的角度范围
        int maxVisible = 0;
        int j = 0;
        for (int i = 0; i < n; i++) {
            // 扩大右边界，直到超出视野范围
            while (j < ang.size() && ang[j] - ang[i] <= ANGLE_RAD + EPS) {
                maxVisible = max(maxVisible, j - i + 1);
                j++;
            }
        }
        
        // 5. 总可见点数 = 非重合点中可覆盖的最大数 + 重合点
        return maxVisible + selfCount;
    }
};