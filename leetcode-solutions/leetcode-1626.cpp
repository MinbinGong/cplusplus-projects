/**
 * 1626. Best Team With No Conflicts
 * 
 * You are the manager of a basketball team. For the upcoming tournament, you want to choose the team with the highest overall score. The score of the team is the sum of scores of all the players in the team.
 * 
 * However, the basketball team is not allowed to have conflicts. A conflict exists if a younger player has a strictly higher score than an older player. A conflict does not occur between players of the same age.
 * 
 * Given two lists, scores and ages, where each scores[i] and ages[i] represents the score and age of the ith player, respectively, return the highest overall score of all possible basketball teams.
 * 
 * Example 1:
 * Input: scores = [1,3,5,10,15], ages = [1,2,3,4,5]
 * Output: 34
 * Explanation: You can choose all the players.
 * 
 * Example 2:
 * Input: scores = [4,5,6,5], ages = [2,1,2,1]
 * Output: 16
 * Explanation: The optimal choice is to choose the first 3 players.
 * 
 * Constraints:
 * 1 <= scores.length, ages.length <= 1000
 * scores.length == ages.length
 * 1 <= scores[i] <= 106
 * 1 <= ages[i] <= 1000
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<pair<int, int>> players; // (age, score)
        for (int i = 0; i < n; ++i) {
            players.push_back({ages[i], scores[i]});
        }
        // 按年龄升序，年龄相同按分数升序排序
        sort(players.begin(), players.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first == b.first) return a.second < b.second;
            return a.first < b.first;
        });
        
        vector<long long> dp(n, 0);
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = players[i].second; // 以 i 结尾的球队至少包含自己
            for (int j = 0; j < i; ++j) {
                if (players[j].second <= players[i].second) { // 满足分数非递减
                    dp[i] = max(dp[i], dp[j] + players[i].second);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};