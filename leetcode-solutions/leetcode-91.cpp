/*
  You have intercepted a secret message encoded as a string of numbers. 
  The message is decoded via the following mapping:
  "1" -> 'A'
  "2" -> 'B'
  ...
  "25" -> 'Y'
  "26" -> 'Z'
  However, while decoding the message, you realize that there are many different ways
  you can decode the message because some codes are contained in other codes ("2" and "5" vs "25").
  For example, "11106" can be decoded into:
  "AAJF" with the grouping (1, 1, 10, 6)
  "KJF" with the grouping (11, 10, 6)
  The grouping (1, 11, 06) is invalid because "06" is not a valid code (only "6" is valid).
  Note: there may be strings that are impossible to decode.

  Given a string s containing only digits, return the number of ways to decode it. 
  If the entire string cannot be decoded in any valid way, return 0. 
*/
#include <string>
#include <vector>
using namespace std;

int numDecodings(string s) {
  if (s.empty()) {
    return 0;
  }

  int prev = s[0] - '0';
  if (prev == 0) {
    return 0;
  }

  int n = s.length();
  if (n == 1) {
    return 1;
  }

  vector<int> dp(n + 1, 1);
  for (int i = 2; i <= n; ++i) {
    int cur = s[i] - '0';
    if ((prev == 0 || prev > 2) && cur == 0) {
      return 0;
    }
    if ((prev < 2 && prev > 0) || prev == 2 && cur < 7) {
      if (cur) {
        dp[i] = dp[i - 2] + dp[i - 1];
      } else {
        dp[i] = dp[i - 2];
      }

    } else {
      dp[i] = dp[i - 1];
    }
    prev = cur;
  }
  return dp[n];
}

int numDecodingsTopDown(string s, int index, vector<int>& memo) {
    if (index == s.length()) {
        return 1;
    }

    if (s[index] == '0') {
        return 0;
    }

    if (memo[index] != -1) {
        return memo[index];
    }

    int ways = numDecodingsTopDown(s, index + 1, memo);

    if (index + 1 < s.length() && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
        ways += numDecodingsTopDown(s, index + 2, memo);
    }

    memo[index] = ways;
    return ways;
}

int numDecodings1(string s) {
    vector<int> memo(s.length(), -1);
    return numDecodingsTopDown(s, 0, memo);
}
           
