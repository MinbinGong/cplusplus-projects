/**
 * 1453. Maximum Number of Darts Inside of a Circular Dartboard
 * 
 * You have a very large square wall and a circular dartboard placed on the wall. You have been challenged to throw darts into the board blindfolded. Darts thrown at the wall are represented as an array of points on a 2D plane. 
 * 
 * Return the maximum number of points that are within or lie on any circular dartboard of radius r.
 * 
 * Example 1:
 * 
 * Input: points = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
 * Output: 4
 * Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.
 * 
 * Example 2:
 * 
 * Input: points = [[-3,0],[3,0],[2,6],[5,4],[0,9],[7,8]], r = 5
 * Output: 5
 * Explanation: Circle dartboard with center in (0,4) and radius = 5 contain all points except the point (7,8).
 * 
 * Note:
 * 1 <= points.length <= 100
 * points[i].length == 2
 * -10^4 <= points[i][0], points[i][1] <= 10^4
 * 1 <= r <= 5000
 */
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numPoints(vector<vector<int>>& points, int r) {
        int n = points.size();
        if (n == 0) return 0;
        const double R = r;
        const double PI = acos(-1.0);
        const double eps = 1e-9;
        int ans = 1;

        for (int i = 0; i < n; ++i) {
            int xi = points[i][0], yi = points[i][1];
            int base = 1;                          // point i itself
            vector<pair<double, int>> events;       // angle, delta

            for (int j = 0; j < n; ++j) {
                if (j == i) continue;
                int xj = points[j][0], yj = points[j][1];
                double dx = xj - xi, dy = yj - yi;
                double d = sqrt(dx * dx + dy * dy);

                if (d < eps) {                       // same point
                    ++base;
                } else if (d <= 2.0 * R + eps) {    // possible to cover both
                    double theta = atan2(dy, dx);
                    double alpha = acos(d / (2.0 * R));
                    double low = theta - alpha;
                    double high = theta + alpha;

                    // normalize to [0, 2π)
                    auto norm = [&](double a) {
                        a = fmod(a, 2.0 * PI);
                        if (a < 0) a += 2.0 * PI;
                        return a;
                    };
                    low = norm(low);
                    high = norm(high);

                    if (low <= high + eps) {
                        events.emplace_back(low, 1);
                        events.emplace_back(high, -1);
                    } else {
                        events.emplace_back(low, 1);
                        events.emplace_back(2.0 * PI, -1);
                        events.emplace_back(0.0, 1);
                        events.emplace_back(high, -1);
                    }
                }
            }

            // sort events: angle ascending, +1 before -1 for same angle
            sort(events.begin(), events.end(),
                 [](const pair<double, int>& a, const pair<double, int>& b) {
                     if (a.first != b.first) return a.first < b.first;
                     return a.second > b.second;   // +1 comes before -1
                 });

            int cur = base;
            ans = max(ans, cur);
            for (auto& e : events) {
                cur += e.second;
                ans = max(ans, cur);
            }
        }
        return ans;
    }
};
