/*
 * Word Search II
 * 
 * Given an m x n board of characters and a list of strings words, return all words on the board.
 * 
 * Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
 * 
 * Example 1:
 * Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
 * Output: ["eat","oath"]
 * 
 * Example 2:
 * Input: board = [["a","b"],["c","d"]], words = ["abcb"]
 * Output: []
 * 
 * Constraints:
 * 1. m == board.length
 * 2. n == board[i].length
 * 3. 1 <= m, n <= 12
 * 4. board[i][j] is a lowercase English letter.
 * 5. 1 <= words.length <= 3 * 10^4
 * 6. 1 <= words[i].length <= 10
 * 7. words[i] consists of lowercase English letters.
 * 8. All the strings of words are unique.
 */
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
private:
    struct TrieNode {
        TrieNode* children[26];
        string word;  // store the word at leaf nodes
        TrieNode() : word("") {
            for (int i = 0; i < 26; ++i) children[i] = nullptr;
        }
    };
    
    TrieNode* buildTrie(vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (const string& w : words) {
            TrieNode* curr = root;
            for (char c : w) {
                int idx = c - 'a';
                if (!curr->children[idx]) {
                    curr->children[idx] = new TrieNode();
                }
                curr = curr->children[idx];
            }
            curr->word = w; // store word at end node
        }
        return root;
    }
    
    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* node, vector<string>& result) {
        char c = board[i][j];
        if (c == '#' || !node->children[c - 'a']) return; // visited or no matching child
        
        node = node->children[c - 'a'];
        if (!node->word.empty()) {
            result.push_back(node->word);
            node->word = ""; // avoid duplicate
        }
        
        board[i][j] = '#'; // mark as visited
        // Explore four directions
        if (i > 0) dfs(board, i - 1, j, node, result);
        if (i < board.size() - 1) dfs(board, i + 1, j, node, result);
        if (j > 0) dfs(board, i, j - 1, node, result);
        if (j < board[0].size() - 1) dfs(board, i, j + 1, node, result);
        board[i][j] = c; // restore
    }
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = buildTrie(words);
        vector<string> result;
        
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                dfs(board, i, j, root, result);
            }
        }
        return result;
    }
};