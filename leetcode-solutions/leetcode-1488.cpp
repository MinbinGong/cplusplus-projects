/**
 * 1488. Avoid Flood in The City
 * 
 * Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it rains over the nth lake, the nth lake becomes full of water. If it rains over a lake that is full of water, there will be a flood. Your goal is to avoid floods in any lake.
 * 
 * Given an integer array rains where:
 * 
 * rains[i] > 0 means there will be rains over the rains[i] lake.
 * rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.
 * Return an array ans where:
 * 
 * ans.length == rains.length
 * ans[i] == -1 if rains[i] > 0.
 * ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
 * If there are multiple valid answers return any of them. If it is impossible to avoid flood return an empty array.
 * 
 * Example 1:
 * Input: rains = [1,2,3,4]
 * Output: [-1,-1,-1,-1]
 * Explanation: After the first day full lakes are [1]
 * After the second day full lakes are [1,2]
 * After the third day full lakes are [1,2,3]
 * After the fourth day full lakes are [1,2,3,4]
 * There's no day to dry any lake and there is no flood in any lake.
 * 
 * Example 2:
 * Input: rains = [1,2,0,0,2,1]
 * Output: [-1,-1,2,1,-1,-1]
 * Explanation: After the first day full lakes are [1]
 * After the second day full lakes are [1,2]
 * After the third day, we dry lake 2. Full lakes are [1]
 * After the fourth day, we dry lake 1. There is no full lakes.
 * After the fifth day, full lakes are [2].
 * Explanation: After the sixth day, there is only one way to dry the lake 2.
 * 
 * Example 3:
 * Input: rains = [1,2,0,1,2]
 * Output: []
 * Explanation: After the second day, full lakes are  [1,2]. We have to dry one lake in the third day.
 * After that, it will rain over lakes [1,2]. It's easy to prove that no matter which lake you choose to dry in the 3rd day, the other one will flood.
 * 
 * Constraints:
 * 1 <= rains.length <= 10^5
 * 0 <= rains[i] <= 10^9
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> ans(n, -1);          // 默认下雨天为-1，晴天后续赋值
        unordered_map<int, int> lastRain; // 记录每个湖泊上一次下雨的日期
        set<int> dryDays;                 // 存储所有晴天的索引

        for (int i = 0; i < n; ++i) {
            if (rains[i] > 0) {           // 下雨天
                int lake = rains[i];
                if (lastRain.count(lake)) {
                    // 该湖泊已下过雨，需要在前面的晴天抽干
                    auto it = dryDays.upper_bound(lastRain[lake]); // 找上一次之后最早的晴天
                    if (it == dryDays.end()) {
                        // 没有可用的晴天，无法避免洪水
                        return {};
                    }
                    ans[*it] = lake;       // 用这个晴天抽干该湖泊
                    dryDays.erase(it);     // 该晴天被使用
                }
                lastRain[lake] = i;        // 更新最后一次下雨日期
                ans[i] = -1;               // 下雨天不能抽水
            } else {                        // 晴天
                dryDays.insert(i);          // 先记录，后续决定抽哪个湖
            }
        }

        // 对于剩余的晴天，任意抽一个湖泊（例如湖泊1）
        for (int d : dryDays) {
            ans[d] = 1;
        }
        return ans;
    }
};