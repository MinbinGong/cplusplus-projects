/**
 * 1742. Maximum Number of Balls in a Box
 * 
 * You are working in a ball factory where you have n balls numbered from lowLimit up to highLimit inclusive (i.e., n == highLimit - lowLimit + 1), and an infinite number of boxes numbered from 1 to infinity.
 * Your job at this factory is to put each ball in the box with a number equal to the sum of digits of the ball's number. For example, the ball number 321 will be put in the box number 3 + 2 + 1 = 6 and the ball number 10 will be put in the box number 1 + 0 = 1.
 * Given two integers lowLimit and highLimit, return the number of balls in the box with the most balls.
 * 
 * Example 1:
 * Input: lowLimit = 1, highLimit = 10
 * Output: 2
 * Explanation:
 * Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
 * Ball Number: 1 2 3 4 5 6 7 8 9 10 11 ...
 * 
 * Example 2:
 * Input: lowLimit = 5, highLimit = 15
 * Output: 2
 * Explanation:
 * Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
 * Ball Number: 5 6 7 8 9 10 11 12 13 14 15 ...
 * 
 * Constraints:
 * 1 <= lowLimit <= highLimit <= 109
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int countBalls(int lowLimit, int highLimit) {
        vector<int> cnt(46, 0); // 数字和最大为 9+9+9+9+9 = 45
        int ans = 0;
        for (int i = lowLimit; i <= highLimit; ++i) {
            int x = i, sum = 0;
            while (x) {
                sum += x % 10;
                x /= 10;
            }
            ++cnt[sum];
            ans = max(ans, cnt[sum]);
        }
        return ans;
    }
};