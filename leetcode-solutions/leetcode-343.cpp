#include <algorithm>
using namespace std;

int integerBreak(int n) {
  vector<int> dp(n + 1, 1);
  for (int j = 2; j <= n; j++) {
    for (int i = 1; i < j; i++) {
      dp[j] = max(dp[j], i * (j - i));
      dp[j] = max(dp[j], i * dp[j - i]);
    }
  }
  return dp[n];
}