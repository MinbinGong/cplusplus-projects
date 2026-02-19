/*
 * Word break II
 * Given a string s and a dictionary of strings wordDict,
 * add spaces in s to construct a sentence where each word is a valid dictionary word.
 * Return all such possible sentences in any order.
 *
 * Note that the same word in the dictionary may be reused multiple times in the segmentation.
 *
 * Example 1:
 * Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
 * Output: ["cats and dog","cat sand dog"]
 *
 * Example 2:
 * Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
 * Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
 *
 * Explanation: Note that you are allowed to reuse a dictionary word.
 *
 * Example 3:
 * Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
 * Output: []
 */
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

void solve(string s, vector<string> &res, unordered_set<string> &st, vector<string> &temp) {
  if (s.length() == 0) {
    string str = "";
    for (auto it : temp) {
      str += it + " ";
    }

    str.pop_back();
    res.push_back(str);
    return;
  }

  for (int i = 0; i < s.length(); i++) {
    if (st.count(s.substr(0, i + 1))) {
      temp.push_back(s.substr(0, i + 1));
      solve(s.substr(i+1), res, st, temp);
      temp.pop_back();
    }
  }
}

vector<string> wordBreak(string s, vector<string>& wordDict) {
  vector<string> res, temp;
  unordered_set<string> st(wordDict.begin(), wordDict.end());

  solve(s, res, st, temp);
  return res;
}
