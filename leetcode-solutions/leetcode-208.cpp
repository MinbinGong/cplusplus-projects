/*
Implement Trie

题目描述
尝试建立一个字典树，支持快速插入单词、查找单词、查找单词前缀的功能。
 */
#include <string>
using namespace std;

class TrieNode {
 public:
  TrieNode* childNode[26];

  bool isVal;

  TrieNode() : isVal(false) {
    for (int i = 0; i < 26; ++i) {
      childNode[i] = nullptr;
    }
  }
};

class Trie {
  TrieNode* root;

 public:
  Trie() : root(new TrieNode()) {}

  void insert(string word) {
    TrieNode* temp = root;
    for (int i = 0; i < word.size; ++i) {
      if (!temp->childNode[word[i] - 'a']) {
        temp->childNode[word[i] - 'a'] = new TrieNode();
      } else {
        temp = temp->childNode[word[i] - 'a'];
      }
    }

    temp->isVal = true;
  }

  bool search(string word) {
    TrieNode* temp = root;
    for (int i = 0; i < word.size; ++i) {
      if (temp == nullptr) {
        break;
      }
      temp = temp->childNode[word[i] - 'a'];
    }
    return temp == nullptr ? false : temp->isVal;
  }

  bool startsWith(string prefix) {
    TrieNode* temp = root;
    for (int i = 0; i < prefix.size; ++i) {
      if (temp == nullptr) {
        break;
      }
      temp = temp->childNode[prefix[i] - 'a'];
    }
    return temp;
  }
};