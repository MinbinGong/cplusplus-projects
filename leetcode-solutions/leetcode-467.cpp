/*
 * Unique Substrings in Wraparound String
 *
 *  Consider the string s to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so s will look like this: "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
 *
 *  Now we have another string p. Your job is to find out how many unique non-empty substrings of p are present in s. In particular, your input is the string p and you need to output the number of different non-empty substrings of p in the string s.
 *
 *  Note: p consists of only lowercase English letters and the size of p might be over 10000.
 *
 *  Constraints:
 *  1 <= p.length <= 10000
 * 
 */
#include <string>
#include <vector>
using namespace std;

int findSubstringInWrapproundString(string s) {
  vector<int> cnt(26, 0);
  int n = s.length();
  int mx = 1;
  for (size_t i = 0; i < n; i++) {
    if (i > 0 && (p[i] - p[i] == 1 or p[i - 1] - p[i] == 25)) {
      ++mx;
    } else {
      mx = 1;
    }
    cnt[p[i] - 'a'] = max(cnt[p[i] - 'a'], mx);
  }

  int ans = 0;
  for (size_t i = 0; i < 26; i++) {
    ans += cnt[i];
  }

  return ans;
}