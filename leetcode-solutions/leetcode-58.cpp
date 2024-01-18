/*
Length of last word


 */
#include <string>
using namespace std;

int lengthOfLastWord(string s) {
  int count = 0;
  bool flag = false;
  for (int i = s.size() - 1; i >= 0; --i) {
    if (s[i] == ' ' && flag) {
      break;
    }

    if (s[i] != ' ') {
      if (!flag) {
        flag = true;
      }
      count++;
    }
  }
  return count;
}