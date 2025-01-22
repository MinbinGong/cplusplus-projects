/*
 * @lc app=leetcode.cn id=583 lang=cpp
 * Delete Operation for Two Strings
 * Given two strings word1 and word2, return the minimum number of steps required to make word1 and word2 the same.
 *
 * In one step, you can delete exactly one character in either string.
 */
#include <string>
#include <vector>

using namespace std;

int longestCommonSubsequence(string& str1, string& str2) {
  int n1 = str1.length();
  int n2 = str2.length();
  vector<int> prev(n2 + 1, 0), curr(n2 + 1, 0);

  for (int i = 0; i < n2 + 1; i++) {
    prev[i] = 0;
  }

  for (int i = 1; i < n1 + 1; i++) {
    for (int j = 1; j < n2 + 1; j++) {
      if (str1[i - 1] == str2[j - 1]) {
        curr[j] = 1 + prev[j - 1];
      } else {
        curr[j] = max(prev[j], curr[j - 1]);
      }
    }
    prev = curr;
  }
  return prev[n2];
}

class Solution {
 public:
  int minDistance(string word1, string word2) {
    int n1 = word1.length();
    int n2 = word2.length();
    int lcs = longestCommonSubsequence(word1, word2);
    return n1 + n2 - 2 * lcs;
  }
};
