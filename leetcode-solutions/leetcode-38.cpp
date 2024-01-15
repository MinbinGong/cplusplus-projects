/*
 * The count-and-say sequence is a sequence of digit strings defined by the recursive formula:
 *  countAndSay(1) = "1"
 *  countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1), which is
 *  then converted into a different digit string.
 * To determine how you "say" a digit string, split it into the minimal number of substrings
 * such that each substring contains exactly one unique digit. Then for each substring, say the
 * number of digits, then say the digit. Finally, concatenate every said digit.
 */
#include <string>

std::string fun(std::string str1) {
  str1 += " ";
  int len = str1.size();
  int count = 1;
  std::string ans = "";

  for (int i = 0; i < len - 1; i++) {
    if (str1[i + 1] == str1[i]) {
      count++;
      continue;
    }

    ans += ('0' + count);
    ans += str1[i];
    count = 1;
  }

  return ans;
}

std::string countAndSay(int n) {
  if (n == 1) return "1";

  std::string x = func(countAndSay(n - 1));
  return x;
}
