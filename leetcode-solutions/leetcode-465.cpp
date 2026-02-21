/*
 * Optimal Account Balancing
 *
 * A group of friends went on holiday and sometimes lent each other money. For example, Alice paid for Bill's lunch for $10. Then later Chris gave Alice $5 for a taxi ride. We can model each transaction as a tuple (x, y, z) which means person x gave person y $z. Assuming Alice, Bill, and Chris are person 0, 1, and 2 respectively (0, 1, 2 are the person's ID), the transactions can be represented as [[0, 1, 10], [2, 0, 5]].
 *
 * Given a list of transactions between a group of people, return the minimum number of transactions required to settle the debt.
 *
 * Constraints:
 * 1 <= transactions.length <= 8
 * transactions[i].length == 3
 * 0 <= transactions[i][0], transactions[i][1] <= 2
 * transactions[i][0] != transactions[i][1]
 * 1 <= transactions[i][2] <= 100
 * 
 */
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        // 1. 计算每个人的净余额
        unordered_map<int, int> balanceMap;
        for (const auto& t : transactions) {
            int from = t[0], to = t[1], amount = t[2];
            balanceMap[from] -= amount;
            balanceMap[to] += amount;
        }

        // 2. 过滤掉余额为0的人，只留下需要结算的
        vector<int> balance;
        for (const auto& p : balanceMap) {
            if (p.second != 0) {
                balance.push_back(p.second);
            }
        }

        // 3. 开始DFS回溯，寻找最小交易次数
        return dfs(balance, 0);
    }

private:
    int dfs(vector<int>& balance, int start) {
        // 跳过已经结清（余额为0）的人
        while (start < balance.size() && balance[start] == 0) {
            start++;
        }
        // 如果所有人都结清了，返回0
        if (start == balance.size()) {
            return 0;
        }

        int minTransactions = INT_MAX;
        // 尝试将 start 的债务与后面的人 (i) 进行结算
        for (int i = start + 1; i < balance.size(); ++i) {
            // 核心剪枝：只有符号相反（一个欠钱，一个应收）的人之间才可能发生交易
            if (balance[start] * balance[i] < 0) {
                // 将 start 的债务转移到 i 身上
                balance[i] += balance[start];
                // 递归处理下一个位置 (start+1)，交易次数+1
                minTransactions = min(minTransactions, 1 + dfs(balance, start + 1));
                // 回溯：恢复原状，尝试下一种可能性
                balance[i] -= balance[start];
            }
        }
        return minTransactions;
    }
};