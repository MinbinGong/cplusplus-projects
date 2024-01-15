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
