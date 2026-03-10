/**
 * 1691. Maximum Height by Stacking Cuboids
 * 
 * Given n cuboids where the dimensions of the ith cuboid is cuboids[i] = [widthi, lengthi, heighti] (0-indexed). Choose a subset of cuboids and place them on each other.
 * 
 * You can place cuboid i on cuboid j if widthi <= widthj and lengthi <= lengthj and heighti <= heightj. You can rearrange any cuboid's dimensions by rotating it to put it on another cuboid.
 * 
 * Return the maximum height of the stacked cuboids.
 * 
 * Example 1:
 * Input: cuboids = [[50,45,20],[95,37,53],[45,23,12]]
 * Output: 190
 * Explanation:
 * Cuboid 1 is placed on the bottom with the 53x37 side facing down with height 95.
 * Cuboid 0 is placed next with the 45x20 side facing down with height 50.
 * Cuboid 2 is placed next with the 23x12 side facing down with height 45.
 * The total height is 95 + 50 + 45 = 190.
 * 
 * Example 2:
 * Input: cuboids = [[38,25,45],[76,35,3]]
 * Output: 76
 * Explanation:
 * You can't place any of the cuboids on the other.
 * We choose cuboid 1 and rotate it so that the 35x3 side is facing down and its height is 76.
 * 
 * Constraints:
 * n == cuboids.length
 * 1 <= n <= 100
 * 1 <= widthi, lengthi, heighti <= 100
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxHeight(vector<vector<int>>& cuboids) {
        // Step 1: sort each cuboid's dimensions
        for (auto& cub : cuboids) {
            sort(cub.begin(), cub.end());
        }
        
        // Step 2: sort all cuboids by dimensions
        sort(cuboids.begin(), cuboids.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] < b[0];
            if (a[1] != b[1]) return a[1] < b[1];
            return a[2] < b[2];
        });
        
        int n = cuboids.size();
        vector<int> dp(n, 0);
        int ans = 0;
        
        // Step 3: DP
        for (int i = 0; i < n; ++i) {
            dp[i] = cuboids[i][2]; // base height with only this cuboid
            for (int j = 0; j < i; ++j) {
                // check if cuboid j can be below cuboid i
                if (cuboids[j][0] <= cuboids[i][0] &&
                    cuboids[j][1] <= cuboids[i][1] &&
                    cuboids[j][2] <= cuboids[i][2]) {
                    dp[i] = max(dp[i], dp[j] + cuboids[i][2]);
                }
            }
            ans = max(ans, dp[i]);
        }
        
        return ans;
    }
};