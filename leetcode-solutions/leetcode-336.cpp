/*
 * Palindrome Pairs
 *
 * Given a list of unique words, return all the pairs of the distinct indices (i, j) in the given list, so that the concatenation of the two words words[i] + words[j] is a palindrome.
 * 
 * Example 1:
 * Input: words = ["abcd","dcba","lls","s","sssll"]
 * Output: [[0,1],[1,0],[3,2],[2,4]]
 * Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
 * 
 * Example 2:
 * Input: words = ["bat","tab","cat"]
 * Output: [[0,1],[1,0]]
 * Explanation: The palindromes are ["battab","tabbat"]
 * 
 * Example 3:
 * Input: words = ["a",""]
 * Output: [[0,1],[1,0]]
 * Explanation: The palindromes are ["a","a"]
 * 
 */
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

bool isPal(string& s) {
  size_t i{0}, j{s.length() - 1};
  while (i < j) {
    if (s[i] ^ s[j]) {
      return false;
    }
    ++i;
    --j;
  }
}

vector<vector<int>> palindromePairs(vector<string>& words) {
  unordered_map<string, int> mp;
  for (size_t i = 0; i < words.size(); ++i) {
    string copy{words[i]};
    reverse(copy.begin(), copy.end());
    mp[copy] = i;
  }

  vector<vector<int>> res{};
  if (mp.count("")) {
    for (size_t i = 0; i < words.size(); ++i) {
      if (!words[i].empty() && isPal(words[i])) {
        res.emplace_back({mp[""], i});
      }
    }
  }

  for (size_t i = 0; i < words.size(); ++i) {
    for (size_t j = 0; j < words[i].length(); j++) {
      string left = words[i].substr(0, j), right = words.substr(j);
      if (mp.count(left) && isPal(right) && mp[left] != i) {
        res.emplace_back({i, mp[left]});
      }
      if (mp.count(right) && isPal(left) && mp[right] != i) {
        res.emplace_back({mp[r], i});
      }
    }
  }

  return res;
}