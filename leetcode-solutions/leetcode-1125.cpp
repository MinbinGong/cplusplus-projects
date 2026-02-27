/**
 * Smallest Sufficient Team
 * 
 * In a project, you have a list of required skills req_skills, and a list of people.
 * The ith person people[i] contains a list of skills that the person has.
 * 
 * Consider a sufficient team: a set of people such that for every required skill in req_skills,
 * there is at least one person in the team who has that skill.
 * We can represent these teams by the index of each person.
 * 
 * For example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].
 * Return any sufficient team of the smallest possible size, represented by the index of each person.
 * You may return the answer in any order.
 * 
 * It is guaranteed an answer exists.
 * 
 * 1 <= req_skills.length <= 16
 * 1 <= req_skills[i].length <= 16
 * req_skills[i] consists of lowercase English letters.
 * All the strings of req_skills are unique.
 * 1 <= people.length <= 60
 * 0 <= people[i].length <= 16
 * 1 <= people[i][j].length <= 16
 * people[i][j] consists of lowercase English letters.
 * All the strings of people[i] are unique.
 * Every skill in people[i] is a skill in req_skills.
 * It is guaranteed a sufficient team exists.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();
        int m = people.size();
        
        // 1. 将技能名称映射到索引 (0 ~ n-1)
        unordered_map<string, int> skillIndex;
        for (int i = 0; i < n; ++i) {
            skillIndex[req_skills[i]] = i;
        }
        
        // 2. 计算每个人的技能掩码 (mask)
        vector<int> personMask(m, 0);
        for (int i = 0; i < m; ++i) {
            for (const string& skill : people[i]) {
                personMask[i] |= (1 << skillIndex[skill]);
            }
        }
        
        // 3. DP 数组：dp[mask] 表示达到该技能状态所需的最优人员集合 (用二进制表示人员)
        // 初始化为全1 (即选择所有人)，但mask=0时为空集
        long long dp[1 << n];
        fill(dp, dp + (1 << n), (1LL << m) - 1); // (1LL<<m)-1 表示选择了所有m个人
        dp[0] = 0; // 不需要任何人就能覆盖空技能
        
        // 4. 动态规划过程 (0/1背包变形)
        for (int i = 0; i < m; ++i) {
            for (int mask = (1 << n) - 1; mask >= 0; --mask) {
                // 不选第i个人的情况已经在dp[mask]中，无需操作
                // 选第i个人的情况
                int newMask = mask | personMask[i];
                long long newTeam = dp[mask] | (1LL << i); // 将第i位标记为1表示选中
                if (__builtin_popcountll(newTeam) < __builtin_popcountll(dp[newMask])) {
                    dp[newMask] = newTeam;
                }
            }
        }
        
        // 5. 从最终状态 dp[(1<<n)-1] 中提取人员编号
        long long teamBits = dp[(1 << n) - 1];
        vector<int> result;
        for (int i = 0; i < m; ++i) {
            if (teamBits >> i & 1) {
                result.push_back(i);
            }
        }
        return result;
    }
};