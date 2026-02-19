/*
 * Word ladder
 *
 * A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words
 * beginWord -> s1 -> s2 -> ... -> sk such that:
 * 1. Every adjacent pair of words differs by a single letter.
 * 2. Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
 * 3. sk == endWord
 *
 * Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences
 * from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of
 * the words [beginWord, s1, s2, ..., sk].
 *
 * Example 1:
 * Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
 * Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
 * Explanation: There are 2 shortest transformation sequences:
 * "hit" -> "hot" -> "dot" -> "dog" -> "cog"
 * "hit" -> "hot" -> "lot" -> "log" -> "cog"
 *
 * Example 2:
 * Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
 * Output: []
 * Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
 *
 * Constraints:
 * 1. 1 <= beginWord.length <= 5
 * 2. endWord.length == beginWord.length
 * 3. 1 <= wordList.length <= 500
 * 4. wordList[i].length == beginWord.length
 * 5. beginWord, endWord, and wordList[i] consist of lowercase English letters.
 * 6. beginWord != endWord
 * 7. All the words in wordList are unique.
 * 8. You may assume no duplicates in wordList.
 */
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void backtracking(const string &src, const string &dst, unordered_map<string, vector<string>> &next,
                  vector<string> &path, vector<vector<string>> &ans) {
  if (src == dst) {
    ans.push_back(path);
    return;
  }

  for (const auto &s : next[src]) {
    path.push_back(s);
    backtracking(s, dst, next, path, ans);
    path.pop_back();
  }
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
  vector<vector<string>> ans;
  unordered_set<string> dict;
  for (const auto &w : wordList) {
    dict.insert(w);
  }

  if (!dict.count(endWord)) {
    return ans;
  }

  dict.erase(beginWord);
  dict.erase(endWord);
  unordered_set<string> q1{beginWord}, q2{endWord};
  unordered_map<string, vector<string>> next;
  bool reversed = false, found = false;
  while (!q1.empty()) {
    unordered_set<string> q;
    for (const auto &w : q1) {
      string s = w;
      for (size_t i = 0; i < s.size(); i++) {
        char ch = s[i];
        for (int j = 0; j < 26; j++) {
          s[i] = j + 'a';
          if (q2.count(s)) {
            reversed ? next[s].push_back(w) : next[w].push_back(s);
            found = true;
          }

          if (dict.count(s)) {
            reversed ? next[s].push_back(w) : next[w].push_back(s);
            q.insert(s);
          }
        }
        s[i] = ch;
      }
    }
    if (found) {
      break;
    }

    for (const auto &w : q) {
      dict.erase(w);
    }

    if (q.size() <= q2.size()) {
      q1 = q;
    } else {
      reversed = !reversed;
      q1 = q2;
      q2 = q;
    }
  }

  if (found) {
    vector<string> path{beginWord};
    backtracking(beginWord, endWord, next, path, ans);
  }

  return ans;
}