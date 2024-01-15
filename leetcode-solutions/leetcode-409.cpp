#include <algorithm>
#include <map>
#include <string>
using namespace std;

int longestPalindrome(string s) {
  map<char, int> m;

  for (char &c : s) m[c]++;

  int oddcnt = count_if(m.begin(), m.end(), [](auto &rhs) { return rhs.second & 1; });

  return s.size() - oddcnt + (oddcnt > 0);
}