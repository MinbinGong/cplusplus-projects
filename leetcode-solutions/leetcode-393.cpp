/*
 * UTF-8 Validation
 * 
 * A character in UTF8 can be from 1 to 4 bytes long, subjected to the following rules:
 * 
 * For a 1-byte character, the first bit is a 0, followed by its Unicode code.
 * For an n-bytes character, the first n bits are all one's, the n + 1 bit is 0, followed by n - 1 bytes with the most significant 2 bits being 10.
 * 
 * Given an array of integers representing the data, return whether it is a valid utf-8 encoding.
 * 
 * Example 1:
 * Input: data = [197,130,1]
 * Output: true
 * Explanation: data represents the octet sequence: 11000101 10000010 00000001.
 * It is a valid utf-8 encoding for a 2-bytes character followed by a 1-byte character.
 * 
 * Example 2:
 * Input: data = [235,140,4]
 * Output: false
 * Explanation: data represented the octet sequence: 11101011 10001100 00000100.
 * The first 3 bits are all one's and the 4th bit is 0 means it is a 3-bytes character.
 * The next byte is a continuation byte which starts with 10 and that's correct.
 * But the second continuation byte does not start with 10, so it is invalid.
 * 
 * Constraints:
 * 1 <= data.length <= 2 * 10^4
 * 0 <= data[i] <= 255
 */
#include <vector>
using namespace std;

int CountOnes(int n) {
  int ones{0};
  while ((n & 0x80) == 0x80) {
    ones++;
    n <<= 1;
  }

  return ones;
}

bool validUtf8(vector<int> &data) {
  int sz = data.size();
  int i = 0;
  while (i < sz) {
    // If the MSBs are 0b00, then skip to next char
    if ((data[i] & 0x80) == 0) {
      i++;
      continue;
    }
    // If MSBs are 0b10 outside of a sequence, return false
    else if ((data[i] & 0xC0) == 0x80)
      return false;
    // If MSBs are 0b11, then we have a sequence, so we'll process the following chars in a subsequence
    else if ((data[i] & 0xC0) == 0xC0) {
      // Count the leading ones
      int ones = CountOnes(data[i]) - 1;
      // A valid UTF-8 sequence is 1-4 bytes, so CountOnes can at most return '4'
      if (ones > 3) return false;
      int n = 0;
      i++;
      while (n < ones) {
        // Check for overflow
        if ((i + n) >= sz) return false;
        // If we have valid index, THEN check for validity of the data
        if ((data[i + n] & 0xC0) != 0x80) return false;
        n++;
      }
      i += ones;
    } else
      return false;
  }
  return true;
}
