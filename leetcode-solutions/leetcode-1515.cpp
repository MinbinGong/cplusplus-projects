/**
 * 1515. Best Position for a Service Centre
 * 
 * A delivery company wants to build a new service centre in a new city. The company knows the positions of all the customers in this city on a 2D-Map and wants to build the new centre in a position such that the sum of the euclidean distances to all customers is minimum.
 * 
 * Given an array positions where positions[i] = [xi, yi] is the position of the ith customer on the map, return the minimum sum of the euclidean distances to all customers.
 * 
 * In other words, you need to choose the position of the service centre [xcentre, ycentre] such that the following formula is minimized:
 * 
 * Answers within 10^-5 of the actual value will be accepted.
 * 
 * Example 1:
 * Input: positions = [[0,1],[1,0],[1,2],[2,1]]
 * Output: 4.00000
 * Explanation: As shown, you can see that choosing [xcentre, ycentre] = [1, 1] will make the distance to each customer = 1, the sum of all distances is 4 which is the minimum possible we can achieve.
 * 
 * Example 2:
 * Input: positions = [[1,1],[3,3]]
 * Output: 2.82843
 * Explanation: The minimum possible sum of distances = sqrt(2) + sqrt(2) = 2.82843
 * 
 * Example 3:
 * Input: positions = [[1,1]]
 * Output: 0.00000
 * 
 * Example 4:
 * Input: positions = [[1,1],[0,0],[2,0]]
 * Output: 2.73205
 * Explanation: At the first glance, you may think that locating the centre at [1, 0] will achieve the minimum sum, but locating it at [1, 0] will make the sum of distances = 3.   
 * 
 * Note:
 * 1 <= positions.length <= 50
 * positions[i].length == 2
 * 0 <= positions[i][0], positions[i][1] <= 100
 * 
 */
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        int n = positions.size();
        if (n == 1) return 0.0;
        
        // 初始点设为所有点的平均值（质心）
        double x = 0, y = 0;
        for (auto& p : positions) {
            x += p[0];
            y += p[1];
        }
        x /= n;
        y /= n;
        
        // 计算初始距离和
        double bestDist = totalDistance(x, y, positions);
        
        // 梯度下降参数
        double step = 50.0;  // 初始步长
        double eps = 1e-7;   // 收敛阈值
        double decay = 0.9;  // 步长衰减系数
        
        // 梯度下降
        while (step > eps) {
            bool improved = false;
            
            // 尝试四个方向：上下左右
            vector<pair<double, double>> directions = {
                {step, 0}, {-step, 0}, {0, step}, {0, -step}
            };
            
            for (auto& dir : directions) {
                double nx = x + dir.first;
                double ny = y + dir.second;
                double dist = totalDistance(nx, ny, positions);
                
                if (dist < bestDist - eps) {
                    bestDist = dist;
                    x = nx;
                    y = ny;
                    improved = true;
                    break;
                }
            }
            
            // 如果没有改进，减小步长
            if (!improved) {
                step *= decay;
            }
        }
        
        return bestDist;
    }
    
private:
    double totalDistance(double x, double y, vector<vector<int>>& positions) {
        double sum = 0.0;
        for (auto& p : positions) {
            double dx = x - p[0];
            double dy = y - p[1];
            sum += sqrt(dx * dx + dy * dy);
        }
        return sum;
    }
};