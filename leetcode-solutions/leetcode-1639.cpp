/*
 * 1639. Number of Ways to Form a Target String Given a Dictionary
 *
 * You are given a list of strings of the same length words and a string target.
 * 
 * Your task is to form target using the given words under the following rules:
 * 
 * target should be formed from left to right.
 * To form the ith character (0-indexed) of target, you can choose the kth character of the jth string in words if target[i] = words[j][k].
 * Once you use the kth character of the jth string of words, you can no longer use the xth character of any string in words where x <= k. In other words, all characters to the left of or at index k become unusuable for every string.
 * Repeat the process until you form the string target.
 * Notice that you can use multiple characters from the same string in words provided the conditions above are met.
 * 
 * Return the number of ways to form target from words. Since the answer may be too large, return it modulo 109 + 7.
 * 
 * Example 1:
 * Input: words = ["acca","bbbb","caca"], target = "aba"
 * Output: 6
 * Explanation: There are 6 ways to form target.
 * "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
 * "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
 * "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
 * "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
 * "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
 * "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")
 * 
 * Example 2:
 * Input: words = ["abba","baab"], target = "bab"
 * Output: 4
 * Explanation: There are 4 ways to form target.
 * "bab" -> index 0 ("abba"), index 1 ("baab"), index 2 ("baab")
 * "bab" -> index 0 ("abba"), index 1 ("baab"), index 3 ("baab")
 * "bab" -> index 0 ("abba"), index 2 ("baab"), index 3 ("baab")
 * "bab" -> index 1 ("baab"), index 2 ("baab"), index 3 ("baab")
 * 
 * Constraints:
 * 1 <= words.length <= 1000
 * 1 <= words[i].length <= 1000
 * All strings in words have the same length.
 * 1 <= target.length <= 1000
 * words[i] and target contain only lowercase English letters.
 * 
 */
#include <array>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Solution1 {
 private:
  int dp[1001][1001];
  long long M = 1e9 + 7;
  vector<map<int, int>> chIdx;

 private:
  long long dfs(string &t, int i, int j) {
    if (i >= chIdx.size()) {
      return j == t.size();
    }
    if (j == t.size()) {
      return 1;
    }
    if (dp[i][j] >= 0) {
      return dp[i][j];
    }
    long long res = 0;
    if (chIdx[i][t[j]]) {
      res = dfs(t, i + 1, j + 1) * chIdx[i][t[j]];
    }
    res += dfs(t, i + 1, j);
    res %= M;
    return dp[i][j] = res;
  }

 public:
  int numWays(vector<string> &words, string target) {
    memset(dp, -1, sizeof(dp));
    chIdx.resize(words[0].size());
    for (auto &word : words) {
      for (int i = 0; i < word.size(); ++i) {
        ++chIdx[i][word[i]];
      }
    }
    return dfs(target, 0, 0);
  }
};

class Solution2 {
 public:
  int numWays(vector<string> &dict, string target) {
    long mod = 1e9 + 7, M = dict.size(), L = dict[0].size(), N = target.size();
    if (L < N) {
      return 0;
    }
    vector<array<long, 26>> cnt(L, array<long, 26>());
    for (int i = 0; i < L; i++) {
      for (int j = 0; j < M; j++) {
        cnt[i][dict[j][i] - 'a']++;
      }
    }
    vector<long> dp(N + 1);
    for (int i = 0; i < L; i++) {
      int prev = 1;
      for (int j = 0; j <= i && j < N; j++) {
        int cur = dp[j + 1];
        dp[j + 1] = ((cnt[i][target[j] - 'a'] * prev) % mod + dp[j + 1] % mod);
        prev = cur;
      }
    }
    return dp[N];
  }
};