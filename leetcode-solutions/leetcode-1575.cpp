/*
 * 1575. Count All Possible Routes
 * 
 * You are given an array of distinct positive integers locations where locations[i] represents the position of city i. You are also given integers start, finish and fuel representing the starting city, ending city, and the initial amount of fuel you have, respectively.
 * 
 * At each step, if you are at city i, you can pick any city j such that j != i and 0 <= j < locations.length and move to city j. Moving from city i to city j reduces the amount of fuel you have by |locations[i] - locations[j]|. Please notice that |x| denotes the absolute value of x.
 * 
 * Notice that fuel cannot become negative at any point in time, and that you are allowed to visit any city more than once (including start and finish).
 * 
 * Return the count of all possible routes from start to finish. Since the answer may be too large, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
 * Output: 4
 * Explanation: The following are all possible routes, each uses 5 units of fuel:
 * 1 -> 3
 * 1 -> 2 -> 3
 * 1 -> 4 -> 3
 * 1 -> 4 -> 2 -> 3
 * 
 * Example 2:
 * Input: locations = [4,3,1], start = 1, finish = 0, fuel = 6
 * Output: 5
 * Explanation: The following are all possible routes:
 * 1 -> 0, used fuel = 1
 * 1 -> 2 -> 0, used fuel = 5
 * 1 -> 2 -> 1 -> 0, used fuel = 5
 * 1 -> 0 -> 1 -> 0, used fuel = 3
 * 1 -> 0 -> 1 -> 0 -> 1 -> 0, used fuel = 5
 * 
 * Constraints:
 * 2 <= locations.length <= 100
 * 1 <= locations[i] <= 10^9
 * All integers in locations are distinct.
 * 0 <= start, finish < locations.length
 * 1 <= fuel <= 200
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        const int MOD = 1e9 + 7;
        int n = locations.size();
        
        // dp[i][f] = number of ways to start at city i with f fuel
        // and eventually end at city 'finish' (including stopping at finish)
        vector<vector<long long>> dp(n, vector<long long>(fuel + 1, 0));
        
        for (int f = 0; f <= fuel; ++f) {
            for (int i = 0; i < n; ++i) {
                // Base case: if we are already at finish, we can stop immediately
                if (i == finish) {
                    dp[i][f] = 1;               // the empty route (stop now)
                }
                
                // Try moving to any other city
                for (int j = 0; j < n; ++j) {
                    if (i == j) continue;        // must travel to a different city
                    int cost = abs(locations[i] - locations[j]);
                    if (cost <= f) {
                        dp[i][f] = (dp[i][f] + dp[j][f - cost]) % MOD;
                    }
                }
            }
        }
        
        return dp[start][fuel] % MOD;
    }
};