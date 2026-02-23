/*
 * Implement Magic Dictionary
 *
 * Implement a magic directory with buildDict, and search methods.
 *
 * For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.
 *
 * For the method search, you'll be given a word, and judge whether if you modify exactly one character into another character in this word, the modified word is in the dictionary you just built.
 *
 * Example 1:
 *
 * Input: buildDict(["hello", "leetcode"]), Output: Null
 * Input: search("hello"), Output: False
 * Input: search("hhllo"), Output: True
 * Input: search("hell"), Output: False
 * Input: search("leetcoded"), Output: False
 * 
 * Note:
 *
 * You may assume that all the inputs are consist of lowercase letters a-z.
 * For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
 * Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are persisted across multiple test cases. Please see here for more details.
 * 
 */
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class MagicDictionary1 {
private:
    unordered_map<int, vector<string>> lenToWords;  // 按长度分组存储

    // 判断两个字符串是否只相差一个字符
    bool isOneCharDiff(const string& a, const string& b) {
        if (a.length() != b.length()) return false;
        int diff = 0;
        for (int i = 0; i < a.length(); i++) {
            if (a[i] != b[i]) diff++;
            if (diff > 1) return false;
        }
        return diff == 1;
    }

public:
    MagicDictionary1() {}
    
    void buildDict(vector<string> dictionary) {
        lenToWords.clear();
        for (const string& word : dictionary) {
            lenToWords[word.length()].push_back(word);
        }
    }
    
    bool search(string searchWord) {
        int len = searchWord.length();
        // 如果没有相同长度的单词，直接返回false
        if (!lenToWords.count(len)) return false;
        
        // 遍历所有相同长度的单词
        for (const string& word : lenToWords[len]) {
            if (isOneCharDiff(word, searchWord)) {
                return true;
            }
        }
        return false;
    }
};

class MagicDictionary2 {
private:
    // key: 模式字符串（如 "h_llo"），value: 匹配该模式的原单词列表
    unordered_map<string, vector<string>> patternToWords;

public:
    MagicDictionary2() {}
    
    void buildDict(vector<string> dictionary) {
        patternToWords.clear();
        for (const string& word : dictionary) {
            // 为每个位置生成一个模式
            string temp = word;
            for (int i = 0; i < word.length(); i++) {
                char original = temp[i];
                temp[i] = '_';  // 通配符
                patternToWords[temp].push_back(word);
                temp[i] = original;  // 恢复
            }
        }
    }
    
    bool search(string searchWord) {
        string temp = searchWord;
        for (int i = 0; i < searchWord.length(); i++) {
            char original = temp[i];
            temp[i] = '_';
            
            // 查找匹配的模式
            if (patternToWords.count(temp)) {
                // 检查是否不是完全相同的单词
                for (const string& word : patternToWords[temp]) {
                    if (word != searchWord) {
                        return true;
                    }
                }
            }
            temp[i] = original;
        }
        return false;
    }
};

class MagicDictionary {
private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEnd;
        TrieNode() : isEnd(false) {
            memset(children, 0, sizeof(children));
        }
    };
    
    TrieNode* root;
    
    // DFS搜索，allowModify表示是否还可以修改一个字符
    bool dfs(const string& word, int pos, TrieNode* node, bool allowModify) {
        if (pos == word.length()) {
            return node->isEnd && !allowModify;  // 必须已经使用过修改机会
        }
        
        int idx = word[pos] - 'a';
        
        // 情况1：不修改当前字符，继续匹配
        if (node->children[idx]) {
            if (dfs(word, pos + 1, node->children[idx], allowModify)) {
                return true;
            }
        }
        
        // 情况2：修改当前字符（如果还有修改机会）
        if (allowModify) {
            for (int i = 0; i < 26; i++) {
                if (i == idx || !node->children[i]) continue;  // 跳过相同字符和不存在的分支
                if (dfs(word, pos + 1, node->children[i], false)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
public:
    MagicDictionary() {
        root = new TrieNode();
    }
    
    void buildDict(vector<string> dictionary) {
        // 清空Trie（简单起见重新创建）
        root = new TrieNode();
        
        // 插入所有单词
        for (const string& word : dictionary) {
            TrieNode* curr = root;
            for (char c : word) {
                int idx = c - 'a';
                if (!curr->children[idx]) {
                    curr->children[idx] = new TrieNode();
                }
                curr = curr->children[idx];
            }
            curr->isEnd = true;
        }
    }
    
    bool search(string searchWord) {
        return dfs(searchWord, 0, root, true);
    }
};