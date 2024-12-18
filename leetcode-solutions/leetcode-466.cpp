#include <string>
using namespace std;

int getMaxRepetitions(string s1, int n1, string s2, int n2) {
  for (auto c : s2) {
    // preventive checkings, it could be O(n), but who cares.
    if (s1.find(c) == string::npos) return 0;
  }
  int p1 = 0, p2 = 0, mark = 0;
  while (p1 < s1.length() * n1) {
    char c = s2[p2 % s2.length()];
    while (s1[p1 % s1.length()] != c && p1 < s1.length() * n1) p1++;
    p2++;
    p1++;
    if (p2 % s2.length() == 0) {
      if (p2 == s2.length()) {
        mark = p1;  // mark the position in s1, when the first s2 ends
      } else if (p1 % s1.length() == mark % s1.length()) {
        int round = (s1.length() * n1 - p1) / (p1 - mark);
        p1 += round * (p1 - mark);
        p2 += round * (p2 - s2.length());
      }
    }
  }
  return p2 / s2.length() / n2;
}