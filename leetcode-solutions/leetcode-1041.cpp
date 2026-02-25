/*
 * 1041. Robot Bounded In Circle
 *
 * On an infinite plane, a robot initially stands at (0, 0) and faces north.  The robot can receive one of three instructions:
 * 
 * "G": go straight 1 unit;
 * "L": turn 90 degrees to the left;
 * "R": turn 90 degress to the right.
 * 
 * Example 1:
 * Input: "GGLLGG"
 * Output: true
 * Explanation: 
 * The robot moves from (0,0) to (0,2), turns 180 degrees, and then returns to (0,0).
 * When repeating these instructions, the robot remains in the circle of radius 2 centered at the origin.
 * 
 * Example 2:
 * Input: "GG"
 * Output: false
 * Explanation: 
 * The robot moves north indefinitely.
 * 
 * Example 3:
 * Input: "GL"
 * Output: true
 * Explanation: 
 * The robot moves from (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0, 0) -> ...
 * 
 * Note:
 * 1. 1 <= instructions.length <= 100
 * 2. instructions[i] is in {'G', 'L', 'R'}
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    bool isRobotBounded(string instructions) {
        // 方向：0-北，1-东，2-南，3-西
        int dir = 0; // 初始朝北
        int x = 0, y = 0; // 初始位置
        
        // 方向数组：对应北、东、南、西的移动
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        // 执行一次指令序列
        for (char ch : instructions) {
            if (ch == 'G') {
                x += directions[dir][0];
                y += directions[dir][1];
            } else if (ch == 'L') {
                dir = (dir + 3) % 4; // 向左转90度
            } else if (ch == 'R') {
                dir = (dir + 1) % 4; // 向右转90度
            }
        }
        
        // 如果回到原点或者方向不是朝北，则会在一个圆内循环
        return (x == 0 && y == 0) || dir != 0;
    }
};