/**
 * 1366. Rank Teams by Votes
 *
 * In a special ranking system, each voter gives a rank from highest to lowest to all teams participated in the competition.
 *
 * The ordering of teams is decided by who received the most position-one votes. If two or more teams tie in the first position, we consider the second position to resolve the conflict, if they tie again, we continue this process until the ties are resolved. If two or more teams are still tied after considering all positions, we rank them alphabetically based on their team letter.
 *
 * Given an array of strings votes which is the votes of all voters in the ranking systems. Sort all teams according to the ranking system described above.
 *
 * Return a string of all teams sorted by the ranking system.
 * 
 * Example 1:
 * Input: votes = ["ABC","ACB","ABC","ACB","ACB"]
 * Output: "ACB"
 * Explanation: Team A was ranked first place by 5 voters. No other team was voted as first place, so team A is the first team.
 * 
 * Team B was ranked second by 2 voters and ranked third by 3 voters.
 * 
 * Example 2:
 * Input: votes = ["WXYZ","XYZW"]
 * Output: "XWYZ"
 * Explanation: X is the winner due to tie-breaking rule. X has same votes as W for the first position but X has one vote as second position, while W does not have any votes as second position. 
 * 
 * Example 3:
 * Input: votes = ["ZMNAGUEDSJYLBOPHRQICWFXTVK"]
 * Output: "ZMNAGUEDSJYLBOPHRQICWFXTVK"
 * Explanation: Only one voter, so their votes are used for the ranking.
 * 
 * Note:
 * 1 <= votes.length <= 1000
 * 1 <= votes[i].length <= 26
 * votes[i].length == votes[j].length for 0 <= i, j < votes.length.
 * votes[i][j] is an English upper-case letter.
 * All characters of votes[i] are unique.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string rankTeams(vector<string>& votes) {
        if (votes.empty()) return "";
        int m = votes[0].size(); // 参赛队伍数量
        vector<vector<int>> rank(26, vector<int>(m, 0)); // 统计每个队伍在每个名次上的得票数

        // 统计票数
        for (const string& vote : votes) {
            for (int i = 0; i < m; ++i) {
                int idx = vote[i] - 'A';
                rank[idx][i]++;
            }
        }

        // 提取所有参赛队伍（以 votes[0] 为准，它是一个排列）
        string teams = votes[0]; 

        // 自定义排序
        sort(teams.begin(), teams.end(), [&](char a, char b) {
            for (int i = 0; i < m; ++i) {
                if (rank[a - 'A'][i] != rank[b - 'A'][i]) {
                    return rank[a - 'A'][i] > rank[b - 'A'][i]; // 票数高的在前
                }
            }
            return a < b; // 所有名次票数相同，按字母升序
        });

        return teams;
    }
};