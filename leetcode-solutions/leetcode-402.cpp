#include <string>
using namespace std;

string remove(string s, int k) {
  if (k == 0) return s;
  if (s.length() == k) return "";
  char c = s[0];
  int ind = 0;
  for (int i = 1; i <= k; i++) {
    if (s[i] < c) {
      c = s[i];
      ind = i;
    }
  }
  return c + remove(s.substr(ind + 1), k - ind);
}

string removeKdigits(string s, int k) {
  int n = s.length();
  if (n == k) return "0";
  string d = remove(s, k);
  while (d[0] == '0' && d != "0") d.erase(d.begin());
  return d;
}