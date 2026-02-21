/*
 * Robot Room Cleaner
 *
 *  You are controlling a robot that is located somewhere in a room. The room is modeled as an m x n binary grid where 0
 * represents a wall and 1 represents an empty slot.
 *
 *  The robot starts at an unknown location in the room that is guaranteed to be empty, and you do not have access to
 * the grid, but you can move the robot using the given API Robot.
 *
 *  You are tasked to use the robot to clean the entire room (i.e., clean every empty cell in the room). The robot with
 * the four given APIs can move forward, turn left, or turn right. Each turn is 90 degrees.
 *
 *  When the robot tries to move into a wall cell, its bumper sensor detects the obstacle, and it stays on the current
 * cell.
 *
 *  Design an algorithm to clean the entire room using the following APIs:
 *
 *  interface Robot {
 *      // returns true if next cell is open and robot moves into the cell.
 *      // returns false if next cell is obstacle and robot stays on the current cell.
 *      boolean move();
 *      // Robot will stay on the same cell after calling turnLeft/turnRight.
 *      // Each turn will be 90 degrees.
 *      void turnLeft();
 *      void turnRight();
 *
 *      // Clean the current cell.
 *      void clean();
 * }
 */
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_set>
#include <string>
using namespace std;

/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 */
class Robot {
 public:
  // Returns true if the cell in front is open and robot moves into the cell.
  // Returns false if the cell in front is blocked and robot stays in the current cell.
  bool move();

  // Robot will stay in the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
};

class Solution {
 public:
  void cleanRoom(Robot& robot) {
    // Use a set to record visited cells. Each cell is stored as "x,y"
    unordered_set<string> visited;
    // Directions: 0 = up, 1 = right, 2 = down, 3 = left
    // Start at (0,0) facing up (direction 0)
    dfs(robot, visited, 0, 0, 0);
  }

 private:
  // The four direction vectors (row, col) corresponding to up, right, down, left
  const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

  void dfs(Robot& robot, unordered_set<string>& visited, int x, int y, int curDir) {
    // Mark the current cell as visited and clean it
    visited.insert(to_string(x) + "," + to_string(y));
    robot.clean();

    // Explore all four directions in clockwise order
    for (int i = 0; i < 4; ++i) {
      int nextDir = (curDir + i) % 4;
      int nx = x + dirs[nextDir][0];
      int ny = y + dirs[nextDir][1];
      string key = to_string(nx) + "," + to_string(ny);

      // If the cell has not been visited and moving is possible
      if (visited.find(key) == visited.end() && robot.move()) {
        dfs(robot, visited, nx, ny, nextDir);
        // Backtrack: return to previous cell and restore orientation
        // Turn around (180°): two rights or two lefts
        robot.turnRight();
        robot.turnRight();
        robot.move();
        // Turn back to original direction: two more rights (or two lefts) restores original orientation?
        // Actually after turning around and moving back, we need to face the original direction.
        // We can either turn left twice or right twice. Let's do two rights to turn around again.
        robot.turnRight();
        robot.turnRight();
      } else {
        // If cannot move or already visited, just turn right to try next direction
        robot.turnRight();
      }
    }
  }
};