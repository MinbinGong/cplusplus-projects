/**
 * 1169. Invalid Transactions
 * 
 * A transaction is possibly invalid if:
 * 
 * the amount exceeds $1000, or;
 * if it occurs within (and including) 60 minutes of another transaction with the same name in a different city.
 * You are given an array of strings transaction where transactions[i] consists of comma-separated values representing the name, time (in minutes), amount, and city of the transaction.
 * 
 * Return a list of transactions that are possibly invalid. You may return the answer in any order.
 * 
 * Example 1:
 * Input: transactions = ["alice,20,800,mtv","alice,50,100,beijing"]
 * Output: ["alice,20,800,mtv","alice,50,100,beijing"]
 * Explanation: The first transaction is invalid because the second transaction occurs within a difference of 60 minutes, have the same name and is in a different city. Similarly the second one is invalid too.
 * 
 * Example 2:
 * Input: transactions = ["alice,20,800,mtv","alice,50,1200,mtv"]
 * Output: ["alice,50,1200,mtv"]
 * Explanation: The transaction is invalid because the amount exceeds $1000.
 * 
 * Example 3:
 * Input: transactions = ["alice,20,800,mtv","bob,50,1200,mtv"]
 * Output: ["bob,50,1200,mtv"]
 * 
 * Note:
 * 1 <= transactions.length <= 1000
 * Each transactions[i] takes the form "{name},{time},{amount},{city}"
 * Each {name} and {city} consist of lowercase English letters, and have lengths between 1 and 10
 * Each {time} consist of digits, and represent an integer between 0 and 1000
 * Each {amount} consist of digits, and represent an integer between 0 and 2000
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <tuple>

class Solution1 {
public:
    std::vector<std::string> invalidTransactions(std::vector<std::string>& transactions) {
        int n = transactions.size();
        std::vector<bool> invalid(n, false);
        std::vector<std::string> name(n), city(n);
        std::vector<int> time(n), amount(n);

        // 1. 解析所有交易
        for (int i = 0; i < n; ++i) {
            std::stringstream ss(transactions[i]);
            std::string token;
            std::vector<std::string> parts;
            while (std::getline(ss, token, ',')) {
                parts.push_back(token);
            }
            name[i] = parts[0];
            time[i] = std::stoi(parts[1]);
            amount[i] = std::stoi(parts[2]);
            city[i] = parts[3];
        }

        // 2. 检查每条交易
        for (int i = 0; i < n; ++i) {
            // 规则 1: 金额超过 1000
            if (amount[i] > 1000) {
                invalid[i] = true;
            }

            // 规则 2: 与同名的另一笔交易在 60 分钟内且在不同城市
            for (int j = i + 1; j < n; ++j) {
                if (name[i] == name[j] && city[i] != city[j] && std::abs(time[i] - time[j]) <= 60) {
                    invalid[i] = true;
                    invalid[j] = true;
                }
            }
        }

        // 3. 收集结果
        std::vector<std::string> result;
        for (int i = 0; i < n; ++i) {
            if (invalid[i]) {
                result.push_back(transactions[i]);
            }
        }
        return result;
    }
};

class Solution2 {
public:
    std::vector<std::string> invalidTransactions(std::vector<std::string>& transactions) {
        std::unordered_map<std::string, std::vector<std::tuple<int, std::string, int>>> nameToTransactions; // 姓名 -> [(时间, 城市, 原始索引)]
        std::unordered_set<int> invalidIndices;

        // 1. 解析交易并按姓名分组
        for (int i = 0; i < transactions.size(); ++i) {
            std::stringstream ss(transactions[i]);
            std::string token;
            std::vector<std::string> parts;
            while (std::getline(ss, token, ',')) {
                parts.push_back(token);
            }
            std::string name = parts[0];
            int t = std::stoi(parts[1]);
            int amt = std::stoi(parts[2]);
            std::string city = parts[3];

            // 规则 1: 金额检查
            if (amt > 1000) {
                invalidIndices.insert(i);
            }

            nameToTransactions[name].emplace_back(t, city, i);
        }

        // 2. 对每组同名交易检查规则 2
        for (auto& [name, transactionsList] : nameToTransactions) {
            int m = transactionsList.size();
            for (int i = 0; i < m; ++i) {
                auto [time_i, city_i, idx_i] = transactionsList[i];
                for (int j = i + 1; j < m; ++j) {
                    auto [time_j, city_j, idx_j] = transactionsList[j];
                    // 如果城市不同且时间差 ≤ 60，则两笔都无效
                    if (city_i != city_j && std::abs(time_i - time_j) <= 60) {
                        invalidIndices.insert(idx_i);
                        invalidIndices.insert(idx_j);
                    }
                }
            }
        }

        // 3. 收集结果
        std::vector<std::string> result;
        for (int idx : invalidIndices) {
            result.push_back(transactions[idx]);
        }
        return result;
    }
};