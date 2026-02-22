/*
 * Design Search Autocomplete System
 *
 * Design a search autocomplete system for a search engine. Users may input a sentence (at least one word and end with a special character '#').
 * 
 * For each character they type except '#', you need to return the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    unordered_set<string> sentences;  // sentences that pass through this node
    TrieNode() {}
};

class AutocompleteSystem {
private:
    TrieNode* root;
    unordered_map<string, int> freq;   // sentence -> frequency
    string currentInput;                // current prefix being typed
    TrieNode* currentNode;               // current Trie node after traversing currentInput

    // Insert a sentence into the Trie
    void insertSentence(const string& sentence) {
        TrieNode* node = root;
        for (char c : sentence) {
            if (!node->children.count(c))
                node->children[c] = new TrieNode();
            node = node->children[c];
            node->sentences.insert(sentence);
        }
    }

public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new TrieNode();
        currentNode = root;
        for (int i = 0; i < sentences.size(); ++i) {
            freq[sentences[i]] += times[i];
            insertSentence(sentences[i]);
        }
    }

    vector<string> input(char c) {
        if (c == '#') {
            // End of current sentence: store it
            freq[currentInput]++;
            insertSentence(currentInput);
            // Reset for next input
            currentInput.clear();
            currentNode = root;
            return {};
        }

        currentInput.push_back(c);
        // If we can't continue in the Trie, no matches
        if (!currentNode || !currentNode->children.count(c)) {
            currentNode = nullptr;  // further characters will also have no matches
            return {};
        }

        currentNode = currentNode->children[c];
        // Collect all sentences at this node
        vector<string> candidates(currentNode->sentences.begin(), currentNode->sentences.end());

        // Sort by: higher frequency first, then lexicographically
        sort(candidates.begin(), candidates.end(), [this](const string& a, const string& b) {
            if (freq[a] == freq[b]) return a < b;
            return freq[a] > freq[b];
        });

        // Return top 3 (or fewer)
        if (candidates.size() > 3) candidates.resize(3);
        return candidates;
    }
};