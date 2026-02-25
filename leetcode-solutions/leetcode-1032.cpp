/*
 * 1032. Stream of Characters
 *
 * Implement the StreamChecker class as follows:
 *
 * StreamChecker(words): Constructor, init the data structure with the given words.
 * query(letter): returns true if and only if for some k >= 1, the last k characters queried (in order from oldest to newest, including this letter just queried) spell one of the words in the given list.
 * 
 * Example:
 * 
 * StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // init the dictionary.
 * streamChecker.query('a');          // return false
 * streamChecker.query('b');          // return false
 * streamChecker.query('c');          // return false
 * streamChecker.query('d');          // return true, because 'cd' is in the wordlist
 * streamChecker.query('e');          // return false
 * streamChecker.query('f');          // return true, because 'f' is in the wordlist
 * streamChecker.query('g');          // return false
 * streamChecker.query('h');          // return false
 * streamChecker.query('i');          // return false
 * streamChecker.query('j');          // return false
 * streamChecker.query('k');          // return false
 * streamChecker.query('l');          // return true, because 'kl' is in the wordlist
 * 
 * Note:
 * 1 <= words.length <= 2000
 * 1 <= words[i].length <= 2000
 * Words will only consist of lowercase English letters.
 * Queries will only consist of lowercase English letters.
 * The number of queries is at most 40000.
 * 
 */
#include <deque>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEnd;

    TrieNode() {
        for (int i = 0; i < 26; ++i) children[i] = nullptr;
        isEnd = false;
    }
};

class StreamChecker {
private:
    TrieNode* root;
    deque<char> buffer;
    int maxWordLen;

public:
    StreamChecker(vector<string>& words) {
        root = new TrieNode();
        maxWordLen = 0;
        for (const string& w : words) {
            maxWordLen = max(maxWordLen, (int)w.size());
            TrieNode* node = root;
            // Insert the word in reverse order
            for (int i = w.size() - 1; i >= 0; --i) {
                int idx = w[i] - 'a';
                if (!node->children[idx])
                    node->children[idx] = new TrieNode();
                node = node->children[idx];
            }
            node->isEnd = true;
        }
    }

    bool query(char letter) {
        buffer.push_back(letter);
        if (buffer.size() > maxWordLen)
            buffer.pop_front();

        TrieNode* node = root;
        // Traverse the buffer from the most recent character backwards
        for (int i = buffer.size() - 1; i >= 0; --i) {
            int idx = buffer[i] - 'a';
            if (!node->children[idx])
                return false;
            node = node->children[idx];
            if (node->isEnd)
                return true;
        }
        return false;
    }
};