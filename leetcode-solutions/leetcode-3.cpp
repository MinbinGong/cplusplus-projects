#include <string>
using namespace std;

int lengthOfLongestSubstring(string s) {
  int array[95] = {0};
  int maxLen = 0;
  int temp = 0;
  int windowStart = 0;
  for (size_t i = 0; i < s.length(); ++i) {
    if (array[s[i] - ' '] == 0) {
      array[s[i] - ' '] = i + 1;
      ++temp;
    } else {
      if (temp > maxLen) {
        maxLen = temp;
      }

      if (array[s[i] - ' '] > windowStart) {
        windowStart = array[s[i] - ' '];
      }

      temp = i + 1 - windowStart;
      array[s[i] - ' '] = i + 1;
    }
  }

  if (temp > maxLen) {
    maxLen = temp;
  }

  return maxLen;
}