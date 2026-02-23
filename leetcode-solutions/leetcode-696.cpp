/*
 * Count Binary Substrings
 * 
 * Given a binary string, count the number of substrings that have an equal number of 0's and 1's.
 * 
 * Example 1:
 * 
 * Input: "00110011"
 * Output: 6
 * Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".
 * 
 * Notice that some of these substrings repeat and are counted the number of times they occur.
 * 
 * Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
 * 
 * Example 2:
 * 
 * Input: "10101"
 * Output: 4
 * Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.
 * 
 * Note:
 * 1. s.length() will be between 1 and 50,000.
 * 2. s will only consist of "0" or "1" characters.
 * 3. s[0] is "1" or "0".
 * 4. s[i] is "1" or "0".
 */
#include <string>
using namespace std;

int countBinarySubstrings(string s) {
  int pre = 0, cur = 1, count = 0;
  for (int i = 1; i < s.length(); ++i) {
    if (s[i] == s[i - 1]) {
      ++cur;
    } else {
      pre = cur;
      cur = 1;
    }

    if (pre >= cur) {
      ++count;
    }
  }
  return count;
}