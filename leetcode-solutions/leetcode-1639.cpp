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