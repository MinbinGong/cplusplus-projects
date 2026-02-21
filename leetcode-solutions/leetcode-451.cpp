/*
 * Sort Characters By Frequency
 *
 * Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.
 *
 * Return the sorted string. If there are multiple answers, return any of them.
 *
 * Constraints:
 * 1 <= s.length <= 5 * 105
 * s consists of uppercase and lowercase English letters and digits.
 * 
 */
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

string frequencySort(string s) {
  vector<pair<int, int>> count(256);
  for (size_t i = 0; i < s.length(); i++) {
    count[s[i]].first++;
  }

  for (size_t i = 0; i < 256; i++) {
    count[i].second = i;
  }

  sort(count.begin(), count.end(), greater<pair<int, int>>());

  string result;
  for (size_t i = 0; i < count.size(); i++) {
    result += string(count[i].first, count[i].second);
  }
  return result;
}

string frequencySort1(string s) {
  unordered_map<char, int> counts;
  for (const char c : s) {
    counts[c]++;
  }

  priority_queue<pair<int, char>> pq;
  for (const auto it : counts) {
    pq.push({it.second, it.first});
  }

  string ret;
  while (!pq.empty())
  {
    auto it = pq.top();
    ret += string(it.first, it.second);
    pq.pop();
  }
  
  return ret;
}