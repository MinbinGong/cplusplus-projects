/*
 * Generate Random Point in a Circle
 *
 * Given the radius and the position of the center of a circle, implement the function randPoint which generates a uniform random point inside the circle.
 * 
 * Constraints:
 * 0 < radius <= 10^6
 * -10^7 <= x_center, y_center <= 10^7
 * randPoint is called at most 3 * 104 times.
 * 
 */
#include <random>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
private:
    double xc, yc, r;
    mt19937 gen;
    uniform_real_distribution<double> dis;

public:
    Solution(double radius, double x_center, double y_center) 
        : xc(x_center), yc(y_center), r(radius), gen(random_device{}()), dis(0.0, 1.0) {}
    
    vector<double> randPoint() {
        double u = dis(gen);      // 用于半径的平方根
        double v = dis(gen);      // 用于角度
        double theta = 2 * M_PI * v;
        double rad = r * sqrt(u); // 使点在圆内均匀分布
        return {xc + rad * cos(theta), yc + rad * sin(theta)};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj->randPoint();
 */