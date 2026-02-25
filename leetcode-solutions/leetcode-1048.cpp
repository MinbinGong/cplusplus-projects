/*
 * 1048. Longest String Chain
 *
 * Given a list of words, each word consists of English lowercase letters.
 * 
 * Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.  For example, "abc" is a predecessor of "abac".
 * 
 * A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.
 * 
 * Return the longest possible length of a word chain with words chosen from the given list of words.
 * 
 * Example 1:
 * Input: ["a","b","ba","bca","bda","bdca"]
 * Output: 4
 * Explanation: the longest word chain is "a","ba","bda","bdca".
 * 
 * Example 2:
 * Input: ["xbc","pcxbcf","xb","cxbc","pcxbc"]
 * Output: 5
 * Explanation: the longest word chain is "xb","xbc","cxbc","pcxbc","pcxbcf".
 * 
 * Note:
 * 1. 1 <= words.length <= 1000
 * 2. 1 <= words[i].length <= 16
 * 3. words[i] only consists of English lowercase letters.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution1 {
public:
    int longestStrChain(vector<string>& words) {
        // 按单词长度排序，确保处理时短单词在前
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.size() < b.size();
        });
        
        // 使用哈希表存储每个单词的最长链长度
        unordered_map<string, int> dp;
        int maxLength = 1; // 至少为1（单个单词）
        
        // 遍历所有单词
        for (const string& word : words) {
            int currentMax = 1; // 当前单词的最长链长度
            
            // 尝试删除每个字符，生成可能的前驱单词
            for (int i = 0; i < word.size(); i++) {
                string predecessor = word.substr(0, i) + word.substr(i + 1);
                
                // 如果前驱单词存在，更新当前单词的最长链长度
                if (dp.find(predecessor) != dp.end()) {
                    currentMax = max(currentMax, dp[predecessor] + 1);
                }
            }
            
            // 记录当前单词的最长链长度
            dp[word] = currentMax;
            maxLength = max(maxLength, currentMax);
        }
        
        return maxLength;
    }
};

class Solution2 {
public:
    int longestStrChain(vector<string>& words) {
        // 按长度分组
        unordered_map<int, vector<string>> lengthGroups;
        for (const string& word : words) {
            lengthGroups[word.size()].push_back(word);
        }
        
        unordered_map<string, int> dp;
        int maxLength = 1;
        
        // 按长度从小到大处理
        for (int len = 1; len <= 16; len++) { // 题目限制单词长度最大为16
            if (lengthGroups.find(len) == lengthGroups.end()) continue;
            
            for (const string& word : lengthGroups[len]) {
                dp[word] = 1; // 初始化为1
                
                // 尝试删除每个字符
                for (int i = 0; i < word.size(); i++) {
                    string predecessor = word.substr(0, i) + word.substr(i + 1);
                    
                    if (dp.find(predecessor) != dp.end()) {
                        dp[word] = max(dp[word], dp[predecessor] + 1);
                    }
                }
                
                maxLength = max(maxLength, dp[word]);
            }
        }
        
        return maxLength;
    }
};

class Solution3 {
public:
    int longestStrChain(vector<string>& words) {
        unordered_set<string> wordSet(words.begin(), words.end());
        unordered_map<string, int> memo;
        
        int maxLength = 0;
        for (const string& word : words) {
            maxLength = max(maxLength, dfs(word, wordSet, memo));
        }
        
        return maxLength;
    }
    
private:
    int dfs(const string& word, unordered_set<string>& wordSet, 
            unordered_map<string, int>& memo) {
        if (memo.find(word) != memo.end()) return memo[word];
        
        int maxLength = 1;
        
        // 尝试删除每个字符
        for (int i = 0; i < word.size(); i++) {
            string predecessor = word.substr(0, i) + word.substr(i + 1);
            
            if (wordSet.find(predecessor) != wordSet.end()) {
                maxLength = max(maxLength, dfs(predecessor, wordSet, memo) + 1);
            }
        }
        
        memo[word] = maxLength;
        return maxLength;
    }
};