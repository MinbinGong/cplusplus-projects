#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string longestCommonPrefix(vector<string> &strs) {
  if (strs.size() == 0) {
    return {};
  }

  sort(strs.begin(), strs.end());
  int n = strs.size() - 1;
  int m = min(strs[0].length(), strs[n].length());

  int i = 0, j = 0;
  while (i < m) {
    if (strs[0][i] == strs[n][i]) {
      ++j;
    } else {
      break;
    }
    ++i;
  }

  return strs[0].substr(0, j);
}