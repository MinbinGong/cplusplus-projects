/*
 * Concatenated Words
 *
 *  Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
 *
 *  A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.
 *
 *  Constraints:
 *  1 <= words.length <= 104
 *  1 <= words[i].length <= 30
 *  words[i] consists of only lowercase English letters.
 *  All the strings of words are unique.
 *  1 <= sum(words[i].length) <= 105
 * 
 */
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

bool dfsHelper(string word, unordered_set<string> &dict, bool first) {
  // Because we need at least two short words to form a concatenated word
  // We use a boolean variable to verify if this is the first time we enter the dfsHelper function

  if (!first && dict.count(word)) {
    return true;
  }

  for (int i = 1; i < word.length(); i++) {
    string tmpStr = word.substr(i);

    if (dict.count(tmpStr)) {
      string rem = word.substr(0, i);
      if (dfsHelper(rem, dict, false)) {
        return true;
      };
    }
  }
  return false;
}

vector<string> findAllConcatenatedWordsInADict(vector<string> &words) {
  unordered_set<string> hs;
  vector<string> results;

  for (auto word : words) {
    if (!hs.count(word)) hs.insert(word);
  }

  for (auto word : words) {
    if (dfsHelper(word, hs, true)) {
      results.push_back(word);
    }
  }
  return results;
}