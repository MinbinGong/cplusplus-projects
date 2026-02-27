/**
 * 1152. Analyze User Website Visit Pattern
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * We are given some website visits: the user with name username[i] visited the website website[i] at time timestamp[i].
 * 
 * A 3-sequence is a list of websites of length 3 sorted in ascending order by the time of their visits.  (The websites in a 3-sequence are not necessarily distinct.)
 * 
 * Find the 3-sequence visited by the largest number of users. If there is more than one solution, return the lexicographically smallest such 3-sequence.
 * 
 * Example 1:
 * Input: username = ["joe","joe","joe","james","james","james","james","mary","mary","mary"], timestamp = [1,2,3,4,5,6,7,8,9,10], website = ["home","about","career","home","cart","maps","home","home","about","career"]
 * Output: ["home","about","career"]
 * Explanation: 
 * The 3-sequence ("home", "about", "career") was visited at least once by 2 users.
 * The 3-sequence ("home", "cart", "maps") was visited at least once by 1 user.
 * The 3-sequence ("home", "cart", "home") was visited at least once by 1 user.
 * The 3-sequence ("home", "maps", "home") was visited at least once by 1 user.
 * The 3-sequence ("cart", "maps", "home") was visited at least once by 1 user.
 * 
 * Example 2:
 * Input: username = ["ua","ua","ua","ub","ub","ub"], timestamp = [1,2,3,4,5,6], website = ["a","b","a","a","b","c"]
 * Output: ["a","b","a"]
 * Explanation: 
 * The 3-sequence ("a", "b", "a") was visited at least once by 2 users.
 * The 3-sequence ("a", "b", "c") was visited at least once by 1 user.
 * The 3-sequence ("b", "a", "b") was visited at least once by 1 user.
 * 
 * Note:
 * 3 <= N = username.length = timestamp.length = website.length <= 50
 * 1 <= username[i].length <= 10
 * 0 <= timestamp[i] <= 10^9
 * 1 <= website[i].length <= 10
 * username[i] and website[i] contain only lowercase characters
 * It is guaranteed that there is at least one user who visited at least 3 websites
 * No user visits two websites at the same time
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        int n = username.size();
        // 1. 按用户分组，记录(时间, 网站)
        unordered_map<string, vector<pair<int, string>>> userMap;
        for (int i = 0; i < n; ++i) {
            userMap[username[i]].emplace_back(timestamp[i], website[i]);
        }

        // 2. 对每个用户的访问按时间排序
        for (auto& entry : userMap) {
            sort(entry.second.begin(), entry.second.end());
        }

        // 3. 统计每个三元组出现的用户数（每个用户只计一次）
        map<vector<string>, int> patternCount;   // 按字典序自动排序
        for (const auto& entry : userMap) {
            const auto& visits = entry.second;
            if (visits.size() < 3) continue;

            set<vector<string>> seen;   // 用于当前用户去重
            for (int i = 0; i + 2 < visits.size(); ++i) {
                vector<string> pattern = {
                    visits[i].second,
                    visits[i+1].second,
                    visits[i+2].second
                };
                seen.insert(pattern);
            }
            for (const auto& pat : seen) {
                patternCount[pat]++;
            }
        }

        // 4. 找到出现用户数最多的三元组，字典序最小优先
        int maxCnt = 0;
        vector<string> result;
        for (const auto& p : patternCount) {
            if (p.second > maxCnt) {
                maxCnt = p.second;
                result = p.first;
            } else if (p.second == maxCnt) {
                if (result.empty() || p.first < result) {
                    result = p.first;
                }
            }
        }
        return result;
    }
};