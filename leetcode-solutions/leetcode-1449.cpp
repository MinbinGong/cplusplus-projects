/**
 * 1449. Form Largest Integer With Digits That Add up to Target
 * 
 * Given an array of integers cost and an integer target. Return the maximum integer you can paint under the following rules:
 * 
 * The cost of painting a digit (i+1) is given by cost[i] (0 indexed).
 * The total cost used must be equal to target.
 * Integer does not have digits 0.
 * 
 * Since the answer may be too large, return it as string.
 * 
 * If there is no way to paint any integer given the condition, return "0".
 * 
 * Example 1:
 * 
 * Input: cost = [4,3,2,5,6,7,2,5,5], target = 9
 * Output: "7772"
 * Explanation:  The cost to paint the digit '7' is 2, and the digit '2' is 3. Then cost("7772") = 2*3+ 3*1 = 9. You could also paint "977", but "7772" is the largest number.
 * 
 * Example 2:
 * 
 * Input: cost = [7,6,5,5,5,6,8,7,8], target = 12
 * Output: "85"
 * Explanation: The cost to paint the digit '8' is 7, and the digit '5' is 5. Then cost("85") = 7*1 + 5*1 = 12.
 * 
 * Example 3:
 * 
 * Input: cost = [2,4,6,2,4,6,4,4,4], target = 5
 * Output: "0"
 * Explanation: It's not possible to paint any integer with total cost equal to target.
 * 
 * Example 4:
 * 
 * Input: cost = [6,10,15,40,40,40,40,40,40], target = 47
 * Output: "32211"
 * 
 * Note:
 * cost.length == 9
 * 1 <= cost[i] <= 5000
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
        // dp[i] = maximum number of digits achievable with total cost i
        vector<int> dp(target + 1, -1);
        dp[0] = 0;

        // compute maximum length for each cost
        for (int i = 1; i <= target; ++i) {
            for (int d = 1; d <= 9; ++d) {
                int c = cost[d - 1];
                if (i >= c && dp[i - c] != -1) {
                    dp[i] = max(dp[i], dp[i - c] + 1);
                }
            }
        }

        // if target cannot be reached, return "0"
        if (dp[target] == -1) return "0";

        // reconstruct the largest number
        string ans;
        int remaining = target;
        int len = dp[target];

        while (remaining > 0) {
            // try the largest digit first
            for (int d = 9; d >= 1; --d) {
                int c = cost[d - 1];
                if (remaining >= c && dp[remaining - c] == len - 1) {
                    ans.push_back('0' + d);
                    remaining -= c;
                    len--;
                    break;
                }
            }
        }
        return ans;
    }
};