#include <array>
#include <string>
#include <vector>
using namespace std;

vector<int> findAnagrams(string s, string p) {
  vector<int> ans{};
  if (s.size() < p.size()) {
    return ans;
  }

  ans.reserve(s.size() - p.size() + 1);  // max possible size is reserved so only one memory alloc is done
  // array of counts for each character
  array<int, 128> counts = {};  // it's faster to use 128 for larger strings to avoid the extra calculations
  for (char c : p) {
    ++counts[c];
  }

  // as we match we decrement this count
  int matches = p.size();

  // keep track of two pointers left and right.  As window widens or shrinks
  // adjust the the match count
  for (int l = 0, r = 0; r < s.size(); ++r) {
    int &rcount = counts[s[r]];
    if (rcount > 0) {
      // we found a character that was in p so claim a match
      --matches;
    }
    rcount--;

    while (matches == 0) {
      // we met one condition to a match: we have all the matches we need in our current window
      int &lcount = counts[s[l]];

      if ((r - l) + 1 == p.size()) {
        // we met the second needed condtion: our window is the same size as p so add l to the answer
        ans.push_back(l);
      }
      // if l was pointing to a character that was in p we need to give back that match
      // as we are about to move l now
      if (lcount >= 0) {
        ++matches;
      }
      ++lcount;
      ++l;
    }
  }

  return ans;
}

vector<int> findAnagrams1(string s, string p) {
  if (s.empty() || p.empty() || s.size() < p.size()) {
    return {};
  }

  vector<int> sf(26, 0), pf(26, 0);
  for (size_t i = 0; i < p.size(); i++) {
    sf[s[i] - 'a']++;
    pf[p[i] - 'a']++;
  }

  vector<int> ans{};
  for (size_t i = 0; i < s.size(); i++) {
    bool flag{true};
    for (size_t j = 0; j < 26; j++) {
      if (sf[j] != pf[j]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      ans.push_back(i - p.size());
    }
    sf[s[i] - 'a']++;
    sf[s[i - p.size()] - 'a']--;
  }

  bool flag{true};
  for (size_t i = 0; i < 26; i++) {
    if (sf[i] != pf[i]) {
      flag = false;
      break;
    }
  }
  if (flag) {
    ans.push_back(s.size() - p.size());
  }
  return ans;
}