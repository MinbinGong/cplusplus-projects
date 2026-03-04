/**
 * 1553. Minimum Number of Days to Eat N Oranges
 * 
 * There are n oranges in the kitchen and you decided to eat some of these oranges every day as follows:
 * 
 * Eat one orange.
 * If the number of remaining oranges (n) is divisible by 2 then you can eat n / 2 oranges.
 * If the number of remaining oranges (n) is divisible by 3 then you can eat 2 * (n / 3) oranges.
 * You can only choose one of the actions per day.
 * 
 * Given the integer n, return the minimum number of days to eat n oranges.
 * 
 * 
 * Example 1:
 * Input: n = 10
 * Output: 4
 * Explanation: You have 10 oranges.
 * Day 1: Eat 1 orange,  10 - 1 = 9.  
 * Day 2: Eat 6 oranges, 9 - 2*(9/3) = 9 - 6 = 3. (Since 9 is divisible by 3)
 * Day 3: Eat 2 oranges, 3 - 2*(3/3) = 3 - 2 = 1. 
 * Day 4: Eat the last orange  1 - 1  = 0.
 * You need at least 4 days to eat the 10 oranges.
 * 
 * Example 2:
 * Input: n = 6
 * Output: 3
 * Explanation: You have 6 oranges.
 * Day 1: Eat 1 orange,  6 - 1 = 5. 
 * Day 2: Eat 2 oranges, 5 - 2*(5/3) = 5 - 2 = 3. (Since 5 is divisible by 3)
 * Day 3: Eat the last orange  3 - 1  = 2.
 * You need at least 3 days to eat the 6 oranges.
 * 
 * Example 3:
 * Input: n = 1
 * Output: 1
 * Explanation: You have 1 orange.
 * Day 1: Eat 1 orange,  1 - 1  = 0.
 * You need at least 1 day to eat the 1 orange.
 * 
 * Constraints:
 * 1 <= n <= 2 * 10^9
 * 
 */
#include <unordered_map>
using namespace std;

class Solution {
public:
    int minDays(int n) {
        // Base cases
        if (n <= 1) return n;
        if (n <= 3) return n;  // n=2 -> 2 days, n=3 -> 2 days (eat 2*(3/3) then 1)
        
        // Memoization: check if already computed
        if (memo.find(n) != memo.end()) {
            return memo[n];
        }
        
        // Two optimal strategies:
        // 1. Reduce to n/2 by eating some oranges one by one first (n%2 days),
        //    then eat half the oranges (1 day), and solve for n/2
        // 2. Reduce to n/3 by eating some oranges one by one first (n%3 days),
        //    then eat 2*(n/3) oranges (1 day), and solve for n/3
        int option1 = n % 2 + 1 + minDays(n / 2);
        int option2 = n % 3 + 1 + minDays(n / 3);
        
        memo[n] = min(option1, option2);
        return memo[n];
    }

private:
    unordered_map<int, int> memo;
};