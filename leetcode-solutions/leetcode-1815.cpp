/*
 * 1815. Maximum Number of Groups Getting Fresh Donuts
 * 
 * There is a donuts shop that bakes donuts in batches of batchSize. They have a rule where they must serve all of the donuts of a batch before serving any donuts of the next batch. You are given an integer batchSize and an integer array groups, where groups[i] denotes that there is a group of groups[i] customers that will visit the shop. Each customer will get exactly one donut.
 * 
 * When a group visits the shop, all customers of the group must be served before serving any of the following groups. A group will be happy if they all get fresh donuts. That is, the first customer of the group does not receive a donut that was left over from the previous group.
 * 
 * You can freely rearrange the ordering of the groups. Return the maximum possible number of happy groups after rearranging the groups.
 * 
 * Example 1:
 * 
 * Input: batchSize = 3, groups = [1,2,3,4,5,6]
 * Output: 4
 * Explanation: It is optimal to group the customers in the following order: [6,2,4,5,1,3]. Then the 4 groups are (6), (2,4), (5,1), (3).
 * Each group has all fresh donuts.
 * 
 * Example 2:
 * 
 * Input: batchSize = 4, groups = [1,3,2,5,2,2,1,6]
 * Output: 4
 * 
 * Constraints:
 * 
 * 1 <= batchSize <= 9
 * 1 <= groups.length <= 30
 * 1 <= groups[i] <= 109
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution1 {
private:
    int batchSize;
    vector<int> cnt; // cnt[i] 表示余数为 i 的组数
    unordered_map<int, int> memo; // 记忆化

    // 将当前各余数的剩余数量编码为一个整数
    int encode(const vector<int>& nums) {
        int code = 0;
        for (int i = 1; i < batchSize; ++i) {
            code = code * (cnt[i] + 1) + nums[i];
        }
        return code;
    }

    // 解码：从整数还原各余数的剩余数量
    vector<int> decode(int state) {
        vector<int> nums(batchSize, 0);
        for (int i = batchSize - 1; i >= 1; --i) {
            int base = cnt[i] + 1;
            nums[i] = state % base;
            state /= base;
        }
        return nums;
    }

    // 深度优先搜索 + 记忆化
    int dfs(int state, int last) {
        if (memo.count(state)) return memo[state];
        
        vector<int> nums = decode(state);
        int res = 0;
        
        // 遍历所有可能的余数，尝试选择一组
        for (int i = 1; i < batchSize; ++i) {
            if (nums[i] < cnt[i]) { // 还有剩余的组
                nums[i]++;
                int nextState = encode(nums);
                // 如果 last == 0，说明这一组会开心
                int gain = (last == 0) ? 1 : 0;
                res = max(res, gain + dfs(nextState, (last + i) % batchSize));
                nums[i]--; // 回溯
            }
        }
        return memo[state] = res;
    }

public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        this->batchSize = batchSize;
        cnt.assign(batchSize, 0);
        
        int ans = 0;
        // 统计余数
        for (int g : groups) {
            int r = g % batchSize;
            if (r == 0) {
                ans++; // 余数为0的组直接开心
            } else {
                cnt[r]++;
            }
        }
        
        // 初始状态：所有剩余组都未被使用，last = 0
        vector<int> init(batchSize, 0);
        int initState = encode(init);
        
        ans += dfs(initState, 0);
        return ans;
    }
};

class Solution2 {
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        int n = batchSize;
        vector<int> cnt(n, 0);
        int ans = 0;
        
        // 预处理
        for (int g : groups) {
            int r = g % n;
            if (r == 0) ans++;
            else cnt[r]++;
        }
        
        // 记忆化搜索
        map<vector<int>, int> memo;
        function<int(int)> dfs = [&](int last) -> int {
            if (memo.count(cnt)) return memo[cnt];
            int res = 0;
            for (int i = 1; i < n; ++i) {
                if (cnt[i] > 0) {
                    cnt[i]--;
                    res = max(res, (last == 0 ? 1 : 0) + dfs((last + i) % n));
                    cnt[i]++;
                }
            }
            return memo[cnt] = res;
        };
        
        return ans + dfs(0);
    }
};
