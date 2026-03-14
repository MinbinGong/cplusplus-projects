/**
 * 1804. Implement Trie II (Prefix Tree)
 * 
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.
 * 
 * Implement the Trie class:
 * 
 * Trie() Initializes the trie object.
 * void insert(String word) Inserts the string word into the trie.
 * int countWordsEqualTo(String word) Returns the number of instances of the string word in the trie.
 * int countWordsStartingWith(String prefix) Returns the number of strings in the trie that have the string prefix as a prefix.
 * void erase(String word) Erases the string word from the trie.
 *  
 * 
 * Example 1:
 * 
 * Input
 * ["Trie", "insert", "insert", "countWordsEqualTo", "countWordsStartingWith", "erase", "countWordsEqualTo", "countWordsStartingWith", "erase", "countWordsStartingWith"]
 * ["", "apple", "apple", "apple", "app", "apple", "app", "app", "app", "app"]
 * Output
 * [null, null, null, 2, 2, null, 1, 1, null, 0]
 * Explanation: All nice pairs (i, j) are as follows:
 * 
 * Example 2:
 * 
 * Input
 * ["Trie", "insert", "insert", "countWordsEqualTo", "countWordsStartingWith", "erase", "countWordsEqualTo", "countWordsStartingWith", "erase", "countWordsStartingWith"]
 * ["", "apple", "apple", "apple", "app", "apple", "app", "app", "app", "app"]
 * Output
 * [null, null, null, 2, 2, null, 1, 1, null, 0]
 * Explanation: All nice pairs (i, j) are as follows:
 * 
 * Constraints:
 * 
 * 1 <= word.length, prefix.length <= 2000
 * word and prefix consist only of lowercase English letters.
 * At most 3 * 104 calls in total will be made to insert, countWordsEqualTo, countWordsStartingWith, and erase.
 * It is guaranteed that for any function call to erase, the string word will exist in the trie.
 * 
 */
#include <vector>
using namespace std;

class Trie {
private:
    // 树节点结构体
    struct TrieNode {
        TrieNode* children[26];        // 子节点指针数组
        int wordCount;                  // 以当前节点结尾的单词数量
        int prefixCount;                // 经过当前节点的单词数量（即以当前路径为前缀的单词数）

        TrieNode() : wordCount(0), prefixCount(0) {
            // 初始化所有子节点为空指针
            for (int i = 0; i < 26; ++i) {
                children[i] = nullptr;
            }
        }
    };

    TrieNode* root;                     // 根节点

    // 辅助函数：根据字符串查找最后一个节点
    TrieNode* findNode(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = ch - 'a';
            // 如果路径中断，说明不存在
            if (curr->children[index] == nullptr) {
                return nullptr;
            }
            curr = curr->children[index];
        }
        return curr;
    }

public:
    Trie() {
        root = new TrieNode();
    }
    
    // 插入单词：沿途增加 prefixCount，结尾增加 wordCount
    void insert(string word) {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode();
            }
            curr = curr->children[index];
            curr->prefixCount++;         // 经过该节点的前缀数 +1
        }
        curr->wordCount++;                // 单词结尾计数 +1
    }
    
    // 返回单词出现的次数
    int countWordsEqualTo(string word) {
        TrieNode* node = findNode(word);
        return node ? node->wordCount : 0;
    }
    
    // 返回以给定前缀开头的单词数量
    int countWordsStartingWith(string prefix) {
        TrieNode* node = findNode(prefix);
        return node ? node->prefixCount : 0;
    }
    
    // 删除一个单词（题目保证单词一定存在）
    void erase(string word) {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = ch - 'a';
            curr = curr->children[index];
            curr->prefixCount--;         // 经过该节点的前缀数 -1
        }
        curr->wordCount--;                // 单词结尾计数 -1
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */