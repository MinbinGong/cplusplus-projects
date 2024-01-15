#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

bool isPal(string& s) {
  size_t i{0}, j{s.length() - 1};
  while (i < j) {
    if (s[i] ^ s[j]) {
      return false;
    }
    ++i;
    --j;
  }
}

vector<vector<int>> palindromePairs(vector<string>& words) {
  unordered_map<string, int> mp;
  for (size_t i = 0; i < words.size(); ++i) {
    string copy{words[i]};
    reverse(copy.begin(), copy.end());
    mp[copy] = i;
  }

  vector<vector<int>> res{};
  if (mp.count("")) {
    for (size_t i = 0; i < words.size(); ++i) {
      if (!words[i].empty() && isPal(words[i])) {
        res.emplace_back({mp[""], i});
      }
    }
  }

  for (size_t i = 0; i < words.size(); ++i) {
    for (size_t j = 0; j < words[i].length(); j++) {
      string left = words[i].substr(0, j), right = words.substr(j);
      if (mp.count(left) && isPal(right) && mp[left] != i) {
        res.emplace_back({i, mp[left]});
      }
      if (mp.count(right) && isPal(left) && mp[right] != i) {
        res.emplace_back({mp[r], i});
      }
    }
  }

  return res;
}