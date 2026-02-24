/*
 * 849. Maximize Distance to Closest Person
 * 
 * In a row of seats, 1 represents a person sitting in that seat, and 0 represents that the seat is empty. 
 * 
 * There is at least one empty seat, and at least one person sitting.
 * 
 * Alex wants to sit in the seat such that the distance between him and the closest person to him is maximized. 
 * 
 * Return that maximum distance to closest person.
 * 
 * Example 1:
 * Input: [1,0,0,0,1,0,1]
 * Output: 2
 * Explanation: 
 * If Alex sits in the second open seat (seats[2]), then the closest person has distance 2.
 * If Alex sits in any other open seat, the closest person has distance 1.
 * Thus, the maximum distance to the closest person is 2.
 * 
 * Example 2:
 * Input: [1,0,0,0]
 * Output: 3
 * Explanation: 
 * If Alex sits in the last seat, the closest person is 3 seats away.
 * Note that Alex may not sit in the last seat.
 * 
 * Note:
 * 1 <= seats.length <= 20000
 * seats contains only 0s or 1s, at least one 0, and at least one 1.
 */
#include <vector>
using namespace std;

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int n = seats.size();
        int prev = -1; // 上一个有人的位置
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            if (seats[i] == 1) {
                if (prev == -1) {
                    // 开头连续空位：从 0 到 i-1 都是空，距离就是 i
                    ans = max(ans, i);
                } else {
                    // 中间连续空位：从 prev+1 到 i-1 都是空，长度为 i - prev - 1
                    int dist = (i - prev) / 2; // 实际最大距离是 ceil(length/2) = (length+1)/2
                    ans = max(ans, dist);
                }
                prev = i;
            }
        }
        // 末尾连续空位：从 prev+1 到 n-1 都是空，长度为 n - prev - 1
        if (prev != n - 1) {
            ans = max(ans, n - prev - 1);
        }
        return ans;
    }
};