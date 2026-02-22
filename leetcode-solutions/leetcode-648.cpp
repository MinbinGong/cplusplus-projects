/*
 * Replace Words
 *
 * In English, we have a concept called root, which can be followed by some other words to form another longer word - let's call this word successor. For example, the root an, followed by other, which can form another word another.
 *
 * Now, given a dictionary consisting of many roots and a sentence. You need to replace all the successor in the sentence with the root forming it. If a successor has many roots can form it, replace it with the root with the shortest length.
 *
 * You need to output the sentence after the replacement.
 *
 * Note:
 *
 * The input will only have lower-case letters.
 * 1 <= dictionary words number <= 1000
 * 1 <= sentence words number <= 1000
 * 1 <= root length <= 100
 * 1 <= sentence words length <= 1000
 * 
 */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Solution {
    struct TrieNode {
        TrieNode* children[26];
        bool isEnd;
        TrieNode() {
            for (int i = 0; i < 26; ++i) children[i] = nullptr;
            isEnd = false;
        }
    };

    TrieNode* root;

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    string searchRoot(const string& word) {
        TrieNode* node = root;
        string prefix;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) break; // no further match
            prefix.push_back(c);
            node = node->children[idx];
            if (node->isEnd) return prefix; // shortest root found
        }
        return word; // no root found
    }

public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        root = new TrieNode();
        for (const string& rootWord : dictionary) {
            insert(rootWord);
        }

        istringstream iss(sentence);
        string word;
        vector<string> result;
        while (iss >> word) {
            result.push_back(searchRoot(word));
        }

        string output;
        for (size_t i = 0; i < result.size(); ++i) {
            if (i > 0) output += " ";
            output += result[i];
        }
        return output;
    }
};