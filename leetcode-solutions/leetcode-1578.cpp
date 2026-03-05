/*
 * 1578. Minimum Time to Make Rope Colorful
 *
 * Alice has n balloons arranged on a rope. You are given a 0-indexed string colors where colors[i] is the color of the ith balloon.
 * Alice wants to make the rope colorful. She does not want two consecutive balloons to be of the same color, so she asks Bob for help. Bob can remove some balloons from the rope to make it colorful. You are given a 0-indexed integer array neededTime where neededTime[i] is the time (in seconds) that Bob needs to remove the ith balloon from the rope.
 * 
 * Return the minimum time Bob needs to make the rope colorful.
 * 
 * Example 1:
 * Input: colors = "abaac", neededTime = [1,2,3,4,5]
 * Output: 3
 * Explanation: In the above image, 'a' is blue, 'b' is red, and 'c' is green.
 * Bob can remove the blue balloon at index 2. This takes 3 seconds.
 * There are no longer two consecutive balloons of the same color. Total time = 3.
 * 
 * Example 2:
 * Input: colors = "abc", neededTime = [1,2,3]
 * Output: 0
 * Explanation: The rope is already colorful. Bob does not need to remove any balloons from the rope.
 * 
 * Example 3:
 * Input: colors = "aabaa", neededTime = [1,2,3,4,1]
 * Output: 2
 * Explanation: Bob will remove the ballons at indices 0 and 4. Each ballon takes 1 second to remove.
 * There are no longer two consecutive balloons of the same color. Total time = 1 + 1 = 2.
 * 
 * Constraints:
 * 1 <= colors.length <= 10^5
 * colors consists of lowercase English letters.
 * neededTime.length == colors.length
 * 1 <= neededTime[i] <= 10^4
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();
        int totalCost = 0;
        int i = 0;
        while (i < n) {
            int j = i;
            int sum = 0;
            int maxTime = 0;
            // process one group of consecutive same color
            while (j < n && colors[j] == colors[i]) {
                sum += neededTime[j];
                maxTime = max(maxTime, neededTime[j]);
                ++j;
            }
            // keep one balloon with maximum time, remove the rest
            totalCost += sum - maxTime;
            i = j;
        }
        return totalCost;
    }
};