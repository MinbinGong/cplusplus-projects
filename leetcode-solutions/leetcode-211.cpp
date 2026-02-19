/*
 * Design Add and Search Words Data Structure
 *
 * Design a data structure that supports adding new words and finding if a string matches any previously added string.
 *
 * Implement the WordDictionary class:
 *
 * WordDictionary() Initializes the object.
 * void addWord(word) Adds word to the data structure, it can be matched later.
 * bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise.
 * word may contain dots '.' where dots can be matched with any letter.
 *
 * Constraints:
 * 1. 1 <= word.length <= 25
 * 2. word in addWord consists of lowercase English letters.
 * 3. word in search consist of '.' or lowercase English letters.
 * 4. There will be at most 3 dots in word for search queries.
 * 5. At most 10^4 calls will be made to addWord and search.
 */

#include <memory>
#include <string>
#include <vector>
using namespace std;

class WordDictionary1 {
 private:
  struct TrieNode {
    std::vector<std::unique_ptr<TrieNode>> children;
    bool isEnd;
    TrieNode() : children(26), isEnd(false) {}
  };

  std::unique_ptr<TrieNode> root;

  // Helper function for recursive search
  bool searchInNode(const std::string& word, int index, TrieNode* node) {
    if (index == word.length()) {
      return node->isEnd;
    }

    char c = word[index];
    if (c == '.') {
      // Try all possible children
      for (int i = 0; i < 26; ++i) {
        if (node->children[i] && searchInNode(word, index + 1, node->children[i].get())) {
          return true;
        }
      }
      return false;
    } else {
      int idx = c - 'a';
      if (!node->children[idx]) return false;
      return searchInNode(word, index + 1, node->children[idx].get());
    }
  }

 public:
  WordDictionary1() : root(std::make_unique<TrieNode>()) {}

  void addWord(const std::string& word) {
    TrieNode* node = root.get();
    for (char c : word) {
      int idx = c - 'a';
      if (!node->children[idx]) {
        node->children[idx] = std::make_unique<TrieNode>();
      }
      node = node->children[idx].get();
    }
    node->isEnd = true;
  }

  bool search(const std::string& word) { return searchInNode(word, 0, root.get()); }
};

class WordDictionary {
  struct TrieNode {
    TrieNode* children[26];
    bool isEnd;
    TrieNode() {
      for (int i = 0; i < 26; ++i) children[i] = nullptr;
      isEnd = false;
    }
  };

  TrieNode* root;

  bool dfs(const string& word, int idx, TrieNode* node) {
    if (idx == word.size()) return node->isEnd;
    char c = word[idx];
    if (c == '.') {
      for (int i = 0; i < 26; ++i) {
        if (node->children[i] && dfs(word, idx + 1, node->children[i])) return true;
      }
      return false;
    } else {
      int i = c - 'a';
      if (!node->children[i]) return false;
      return dfs(word, idx + 1, node->children[i]);
    }
  }

 public:
  WordDictionary() { root = new TrieNode(); }

  ~WordDictionary() {
    // recursively delete nodes (implementation omitted for brevity)
  }

  void addWord(string word) {
    TrieNode* cur = root;
    for (char c : word) {
      int i = c - 'a';
      if (!cur->children[i]) cur->children[i] = new TrieNode();
      cur = cur->children[i];
    }
    cur->isEnd = true;
  }

  bool search(string word) { return dfs(word, 0, root); }
};