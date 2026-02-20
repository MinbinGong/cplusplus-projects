/*
 * Maximum Product of Word Lengths
 * 
 * Given a string array words, return the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters.
 * If no such two words exist, return 0.
 * 
 * Example 1:
 * Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
 * Output: 16
 * Explanation: The two words can be "abcw", "xtfn".
 * 
 * Example 2:
 * Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
 * Output: 4
 * Explanation: The two words can be "ab", "cd".
 * 
 * Example 3:
 * Input: words = ["a","aa","aaa","aaaa"]
 * Output: 0
 * Explanation: No such pair of words.
 * 
 */
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int maxProduct(vector<string>& words) {
  unordered_map<int, int> hash;
  int ans = 0;
  for (const string& word : words) {
    int mask = 0, size = word.size();
    for (const char& c : word) {
      mask |= 1 << (c - 'a');
    }

    hash[mask] = max(hash[mask], size);
    for (const auto& [hmask, hlen] : hash) {
      if (!(mask & hmask)) {
        ans = max(ans, size * hlen);
      }
    }
  }

  return ans;
}