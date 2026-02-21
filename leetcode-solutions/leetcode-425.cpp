/*
 * Word Squares
 *
 * Given an array of strings words, return all word squares you can build from words. The same word from words can be used multiple times. You can return the answer in any order.
 * A sequence of strings forms a valid word square if the kth row and column read the same string, where 0 <= k < max(numRows, numColumns).
 * For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word reads the same both horizontally and vertically.
 * 
 * Example 1:
 * Input: words = ["area","lead","wall","lady","ball"]
 * Output: [["ball","area","lead","lady"],["wall","area","lead","lady"]]
 * Explanation:
 * The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
 * 
 * Example 2:
 * Input: words = ["abat","baba","atan","atal"]
 * Output: [["baba","abat","baba","atal"],["baba","abat","baba","atan"]]
 * Explanation:
 * The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
 * 
 * Constraints:
 * 1 <= words.length <= 1000
 * 1 <= words[i].length <= 4
 * All words[i] have the same length.
 * words[i] consists of only lowercase English letters.
 * 
 */
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Solution {
public:
    struct TrieNode {
        TrieNode* next[26];
        vector<int> ids;               // 以当前前缀开头的单词索引
        TrieNode() {
            memset(next, 0, sizeof(next));
        }
    };

    vector<vector<string>> wordSquares(vector<string>& words) {
        vector<vector<string>> res;
        if (words.empty()) return res;
        int n = words.size();
        int L = words[0].size();        // 所有单词等长

        // 构建前缀树，根节点也存储所有单词（空前缀）
        TrieNode* root = new TrieNode();
        for (int i = 0; i < n; ++i) {
            TrieNode* node = root;
            node->ids.push_back(i);     // 空前缀包含所有单词
            for (char c : words[i]) {
                int idx = c - 'a';
                if (!node->next[idx]) node->next[idx] = new TrieNode();
                node = node->next[idx];
                node->ids.push_back(i);
            }
        }

        vector<bool> used(n, false);
        vector<int> path;
        dfs(0, path, res, words, root, used);
        return res;
    }

private:
    void dfs(int step, vector<int>& path, vector<vector<string>>& res,
             vector<string>& words, TrieNode* root, vector<bool>& used) {
        int L = words[0].size();
        if (step == L) {
            vector<string> square;
            for (int idx : path) square.push_back(words[idx]);
            res.push_back(square);
            return;
        }

        // 计算当前行需要满足的前缀：由前面行的第 step 列字符组成
        string prefix;
        for (int i = 0; i < step; ++i) {
            prefix += words[path[i]][step];
        }

        // 在前缀树中定位到该前缀
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->next[idx]) return;   // 无匹配前缀
            node = node->next[idx];
        }

        // 遍历所有以此前缀开头的单词
        for (int id : node->ids) {
            if (!used[id]) {
                used[id] = true;
                path.push_back(id);
                dfs(step + 1, path, res, words, root, used);
                path.pop_back();
                used[id] = false;
            }
        }
    }
};