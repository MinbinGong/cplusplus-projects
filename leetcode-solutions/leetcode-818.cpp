/*
 * 818. Race Car
 * 
 * Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)
 * 
 * Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).
 * 
 * When you get an instruction "A", your car does the following: position += speed, speed *= 2.
 * 
 * When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)
 * 
 * For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.
 * 
 * Now for some target position, say the length of the shortest sequence of instructions to get there.
 * 
 * Example:
 * Input: target = 3
 * Output: 2
 * Explanation: 
 * The shortest instruction sequence is "AA".
 * Your position goes from 0->1->3.
 * 
 * Note:
 * 1 <= target <= 10000.
 */
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    int racecar(int target) {
        if (target == 0) return 0;
        int maxPos = 2 * target;          // 位置不会超过 2*target
        int maxSpeed = 2 * target;        // 速度绝对值不会超过 2*target
        int offset = maxSpeed;             // 用于将速度映射为非负数

        // 队列存储 (位置, 速度, 步数)
        queue<tuple<int, int, int>> q;
        unordered_set<long long> visited;

        // 编码状态：高16位为位置，低16位为速度+偏移
        auto encode = [&](int pos, int speed) {
            return ((long long)pos << 16) + (speed + offset);
        };

        q.push({0, 1, 0});
        visited.insert(encode(0, 1));

        while (!q.empty()) {
            auto [pos, speed, steps] = q.front();
            q.pop();

            if (pos == target) return steps;

            // 操作 A：加速
            int newPos = pos + speed;
            int newSpeed = speed * 2;
            if (newPos >= 0 && newPos <= maxPos && abs(newSpeed) <= maxSpeed) {
                long long key = encode(newPos, newSpeed);
                if (!visited.count(key)) {
                    visited.insert(key);
                    q.push({newPos, newSpeed, steps + 1});
                }
            }

            // 操作 R：反向
            newSpeed = (speed > 0) ? -1 : 1;
            newPos = pos;
            if (abs(newSpeed) <= maxSpeed) {
                long long key = encode(newPos, newSpeed);
                if (!visited.count(key)) {
                    visited.insert(key);
                    q.push({newPos, newSpeed, steps + 1});
                }
            }
        }
        return -1; // 理论上不会执行到这里
    }
};