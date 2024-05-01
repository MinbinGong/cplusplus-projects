/*
 * Repeated DNA Sequences
 *
 * The DNA sequence is composed of a series of nucleotides abbreviated as 'A',
 * 'C', 'G', and 'T'.
 *
 * For example, "ACGAATTCCG" is a DNA sequence.
 * When studying DNA, it is useful to identify repeated sequences within the
 * DNA.
 *
 * Given a string s that represents a DNA sequence, return all the
 * 10-letter-long sequences (substrings) that occur more than once in a DNA
 * molecule. You may return the answer in any order.
 *
 *
 *
 * Example 1:
 *
 * Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
 * Output: ["AAAAACCCCC","CCCCCAAAAA"]
 * Example 2:
 *
 * Input: s = "AAAAAAAAAAAAA"
 * Output: ["AAAAAAAAAA"]
 *
 * Constraints:
 *
 * 1 <= s.length <= 105
 * s[i] is either 'A', 'C', 'G', or 'T'.
 */
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<string> findRepeatedDnaSequences(string s) {
  vector<string> res;
  long long hash = 0;
  int n = s.length();
  vector<int> inp(n);
  unordered_map<long long, int> m;
  if (n < 10) {
    return res;
  }

  for (int i = 0; i < n; i++) {
    if (s[i] == 'A') {
      inp[i] = 1;
    } else if (s[i] == 'C') {
      inp[i] = 2;
    } else if (s[i] == 'G') {
      inp[i] = 3;
    } else {
      inp[i] = 4;
    }
  }

  for (int i = 0; i < 10; i++) {
    hash = hash * 4 + inp[i];
  }

  m[hash]++;
  for (int i = 1; i < n - 9; i++) {
    hash = hash * 4 - inp[i - 1] * pow(4, 10) + inp[i + 9];
    m[hash]++;
    if (m[hash] == 2) {
      res.push_back(s.substr(i, 10));
    }
  }
  return res;
}
