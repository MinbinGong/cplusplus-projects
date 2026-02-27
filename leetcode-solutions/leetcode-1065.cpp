/**
 * 1065. Index Pairs of a String
 * 
 * Given a text string and words (a list of strings), return all index pairs [i, j] so that the substring text[i]...text[j] is in the list of words.
 * 
 * 
 * Example 1:
 * Input: text = "thestoryofleetcodeandme", words = ["story","fleet","leetcode"]
 * Output: [[3,7],[9,13],[10,17]]
 * 
 * Example 2:
 * Input: text = "ababa", words = ["aba","ab"]
 * Output: [[0,1],[0,2],[2,3],[2,4]]
 * Explanation: 
 * Notice that matches can overlap, see "aba" is found in [0,2] and [2,4].
 * 
 * Note:
 * All strings contains only lowercase English letters.
 * It's guaranteed that all strings in words are different.
 * 1 <= text.length <= 100
 * 1 <= words.length <= 20
 * 1 <= words[i].length <= 50
 * Return the pairs [i,j] in sorted order (i.e. sort them by their first coordinate in case of ties sort them by their second coordinate).
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<int>> indexPairs(string text, vector<string>& words) {
        // 构建 Trie 树
        struct TrieNode {
            TrieNode* next[26] = {nullptr};
            bool isEnd = false;
        };
        TrieNode* root = new TrieNode();
        
        // 将所有单词插入 Trie
        for (const string& w : words) {
            TrieNode* node = root;
            for (char c : w) {
                int idx = c - 'a';
                if (!node->next[idx]) {
                    node->next[idx] = new TrieNode();
                }
                node = node->next[idx];
            }
            node->isEnd = true;  // 标记单词结尾
        }
        
        vector<vector<int>> ans;
        int n = text.size();
        
        // 遍历每个起始位置 i
        for (int i = 0; i < n; ++i) {
            TrieNode* node = root;
            int j = i;
            // 从 i 开始不断扩展结束位置 j
            while (j < n && node->next[text[j] - 'a']) {
                node = node->next[text[j] - 'a'];
                if (node->isEnd) {
                    ans.push_back({i, j});  // 找到一个单词 [i, j]
                }
                ++j;
            }
        }
        
        // 由于遍历顺序为 i 递增、同一 i 下 j 递增，结果已经按题意排序，无需再次排序
        return ans;
    }
};