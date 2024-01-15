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