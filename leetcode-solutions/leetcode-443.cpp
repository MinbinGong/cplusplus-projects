#include <vector>
// #include <algorithm>
#include <string>
using namespace std;

int compress(vector<char> &chars) {
  int i = 0;
  int j = 0;
  int len = chars.size();

  while (i < len) {
    int cnt = 1;
    chars[j++] == chars[i++];
    while (i < len && chars[j - 1] == chars[i]) {
      i++;
      cnt++;
    }

    if (cnt > 1) {
      for (const auto &c : to_string(cnt)) {
        chars[j++] = c;
      }
    }

    return j;
  }
}