/**
 * 1554. Strings Differ by One Character
 * 
 * Given a list of strings dict where all the strings are of the same length.
 * 
 * Return true if there are 2 strings that only differ by 1 character in the same index, otherwise return false.
 * 
 * 
 * Example 1:
 * Input: dict = ["abcd","acbd", "aacd"]
 * Output: true
 * Explanation: Strings "abcd" and "aacd" differ only by one character in the index 1.
 * 
 * Example 2:
 * Input: dict = ["ab","cd","yz"]
 * Output: false
 * 
 * Example 3:
 * Input: dict = ["abcd","cccc","abyd","abab"]
 * Output: true
 * 
 * Constraints:
 * 2 <= dict.length <= 10^5
 * 1 <= dict[i].length <= 100
 * dict[i] consists of lowercase English letters.
 * 
 */
#include <vector>
#include <string>
#include <unordered_set>

class Solution {
public:
    bool differByOne(std::vector<std::string>& dict) {
        int n = dict.size();
        int m = dict[0].size();
        const long long MOD = 10000000000000007L; // 一个足够大的模数
        std::vector<long long> word_hash(n, 0);

        // 1. 计算每个字符串的哈希值
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                word_hash[i] = (word_hash[i] * 26 + (dict[i][j] - 'a')) % MOD;
            }
        }

        long long base = 1;
        // 2. 枚举要跳过的位置 j (从右向左处理，方便计算base)
        for (int j = m - 1; j >= 0; --j) {
            std::unordered_set<long long> seen;
            for (int i = 0; i < n; ++i) {
                // 计算删掉 dict[i][j] 后字符串的哈希值
                // 原哈希减去当前字符的贡献： (char_val * base) % MOD
                long long char_val = dict[i][j] - 'a';
                long long hash_without_j = (word_hash[i] - (char_val * base) % MOD + MOD) % MOD;

                if (seen.count(hash_without_j)) {
                    return true;
                }
                seen.insert(hash_without_j);
            }
            // base 更新为 26^j 的值，用于下一轮循环
            base = (base * 26) % MOD;
        }
        return false;
    }
};