/*
 * 1776. Car Fleet II
 *
 * There are n cars traveling at different speeds in the same direction along a one-lane road. You are given an array cars of length n, where cars[i] = [positioni, speedi] represents:
 * 
 * positioni is the distance between the ith car and the beginning of the road in meters. It is guaranteed that positioni < positioni+1.
 * speedi is the initial speed of the ith car in meters per second.
 * 
 * For simplicity, cars can be considered as points moving along the number line. Two cars collide when they occupy the same position. Once a car collides with another car, they unite and form a single car fleet. The cars in the formed fleet will have the same position and the same speed, which is the initial speed of the slowest car in the fleet.
 * 
 * Return an array answer, where answer[i] is the time, in seconds, at which the ith car collides with the next car, or -1 if the car does not collide with the next car. Answers within 10-5 of the actual answers are accepted.
 * 
 * Example 1:
 * 
 * Input: cars = [[1,2],[2,1],[4,3],[7,2]]
 * Output: [1.00000,-1.00000,3.00000,-1.00000]
 * Explanation: After exactly one second, the first car will collide with the second car, and form a car fleet with speed 1 m/s. After exactly 3 seconds, the third car will collide with the fourth car, and form a car fleet with speed 2 m/s.
 * 
 * Example 2:
 * 
 * Input: cars = [[3,4],[5,4],[6,3],[9,1]]
 * Output: [2.00000,1.00000,1.50000,-1.00000]
 * Explanation: After exactly 2 seconds, the first car will collide with the second car, and form a car fleet with speed 4 m/s. After exactly 1 second, the third car will collide with the fourth car, and form a car fleet with speed 3 m/s. After exactly 3/2 seconds, the third car will collide with the fourth car, and form a car fleet with speed 1 m/s.
 * 
 * Constraints:
 * 
 * n == cars.length
 * 1 <= n <= 105
 * 1 <= positioni, speedi <= 106
 * positioni < positioni+1
 * 
 */
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int n = cars.size();
        vector<double> ans(n, -1.0);  // 初始化答案数组，默认为 -1（不会相遇）
        stack<int> stk;               // 单调栈，存储车辆索引
        
        // 从最右边的车开始向左遍历
        for (int i = n - 1; i >= 0; --i) {
            int pos_i = cars[i][0], speed_i = cars[i][1];
            
            while (!stk.empty()) {
                int j = stk.top();      // 当前栈顶的车（i 右边的车）
                int pos_j = cars[j][0], speed_j = cars[j][1];
                
                // 情况1：如果我的速度 <= 前车速度，永远追不上前车
                if (speed_i <= speed_j) {
                    stk.pop();           // 前车不可能被我追上，弹出
                }
                // 情况2：我能追上 j，但需要计算时间
                else {
                    double time = (double)(pos_j - pos_i) / (speed_i - speed_j);
                    
                    // 如果 j 的答案不是 -1，且我追上 j 的时间 > j 追上别人的时间
                    // 说明在追上 j 之前，j 已经和别人合并了，所以实际上我要追的是更前面的车
                    if (ans[j] > 0 && time >= ans[j]) {
                        stk.pop();       // j 已经先和别人合并了，弹出
                    } else {
                        // 否则，我会追上 j，记录时间并跳出循环
                        ans[i] = time;
                        break;
                    }
                }
            }
            stk.push(i);  // 当前车入栈
        }
        return ans;
    }
};