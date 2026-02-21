/*
 * Reconstruct Original Digits from English
 *
 * Given a non-empty string containing an out-of-order English representation of digits 0-9, output the digits in ascending order.
 * 
 * Note:
 * Input contains only lowercase English letters.
 * Input is guaranteed to be valid and can be transformed to its original digits. That means invalid inputs such as "abc" or "zerone" are not permitted.
 * Input length is less than 50,000.
 * 
 * Example 1:
 * Input: s = "owoztneoer"
 * Output: "012"
 *
 * Example 2:
 * Input: s = "fviefuro"
 * Output: "45"
 * 
 * Constraints:
 * 1 <= s.length <= 105
 * 
 */
#include <string>
#include <vector>
using namespace std;

string originalDigits(string s) {
  vector<int> alphaCount(256, 0);
  for (int i = 0; i < s.size(); i++) {
    alphaCount[s[i]]++;
  }
  vector<int> numBin(10, 0);
  string numStr[] = {"zero", "eight", "three", "two", "four", "five", "seven", "one", "six", "nine"};
  char specChar[] = {'z', 'g', 'h', 't', 'r', 'f', 'v', 'o', 'x', 'i'};
  int numOrder[] = {0, 8, 3, 2, 4, 5, 7, 1, 6, 9};
  for (int i = 0; i < 10; i++) {
    int num = numOrder[i];
    string &s = numStr[i];
    char c = specChar[i];
    int count = alphaCount[c];
    numBin[num] += count;
    for (int i = 0; i < s.size(); i++) {
      alphaCount[s[i]] -= count;
    }
  }
  string ret;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < numBin[i]; j++) {
      ret += ('0' + i);
    }
  }
  return ret;
}
