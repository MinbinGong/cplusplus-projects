/*
 * Alien Dictionary
 * 
 * There is a new alien language that uses the English alphabet. 
 * However, the order among the letters is unknown to you.
 * You are given a list of strings words from the alien language's dictionary,
 * where the strings in words are sorted lexicographically by the rules of this new language.
 * 
 * Return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules.
 * If there is no solution, return "". If there are multiple solutions, return any of them.
 * 
 * Constraints:
 * 1. 1 <= words.length <= 100
 * 2. 1 <= words[i].length <= 100
 * 3. words[i] consists of only lowercase English letters.
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// 时间复杂度：O(nk)
// 空间复杂度：O(k)
// 拓扑排序
class Solution {
public:
    string alienOrder(vector<string>& words) {
        // Build graph and indegree
        unordered_map<char, vector<char>> graph;
        unordered_map<char, int> indegree;
        
        // Step 1: Initialize all characters with indegree 0
        for (const string& word : words) {
            for (char c : word) {
                indegree[c] = 0;
                graph[c] = vector<char>();
            }
        }
        
        // Step 2: Extract edges from adjacent words
        for (int i = 0; i < words.size() - 1; ++i) {
            string w1 = words[i];
            string w2 = words[i + 1];
            
            // Check for invalid prefix case
            if (w1.size() > w2.size() && w1.substr(0, w2.size()) == w2) {
                return "";
            }
            
            // Find first differing character
            int minLen = min(w1.size(), w2.size());
            for (int j = 0; j < minLen; ++j) {
                if (w1[j] != w2[j]) {
                    // Add edge w1[j] → w2[j]
                    if (find(graph[w1[j]].begin(), graph[w1[j]].end(), w2[j]) 
                        == graph[w1[j]].end()) {
                        graph[w1[j]].push_back(w2[j]);
                        indegree[w2[j]]++;
                    }
                    break;  // Only the first difference matters
                }
            }
        }
        
        // Step 3: Kahn's algorithm (BFS)
        queue<char> q;
        for (auto& p : indegree) {
            if (p.second == 0) {
                q.push(p.first);
            }
        }
        
        string result;
        while (!q.empty()) {
            char u = q.front();
            q.pop();
            result.push_back(u);
            
            for (char v : graph[u]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        // Step 4: Check for cycle
        if (result.size() != indegree.size()) {
            return "";
        }
        return result;
    }
};