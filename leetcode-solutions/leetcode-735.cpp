/*
 * Asteroid Collision
 *
 * We are given an array asteroids of integers representing asteroids in a row.
 * 
 * For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.
 * 
 * Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.
 * 
 * Note:
 * 1. The length of asteroids will be at most 10000.
 * 2. Each asteroid will be a non-zero integer in the range [-1000, 1000]..
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> result; // use as a stack

        for (int a : asteroids) {
            bool destroyed = false;

            // While there is a right-moving asteroid on the stack and current is left-moving
            while (!result.empty() && result.back() > 0 && a < 0) {
                int top = result.back();
                if (abs(top) < abs(a)) {
                    // Top explodes, remove it and continue checking
                    result.pop_back();
                } else if (abs(top) == abs(a)) {
                    // Both explode, remove top and mark current as destroyed
                    result.pop_back();
                    destroyed = true;
                    break;
                } else {
                    // Current asteroid explodes (top is larger)
                    destroyed = true;
                    break;
                }
            }

            if (!destroyed) {
                result.push_back(a);
            }
        }

        return result;
    }
};