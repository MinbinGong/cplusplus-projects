#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

int minMutation(string start, string end, vector<string> &bank) {
  unordered_set<string> dict;
  unordered_set<string> visited;
  for (const string s : bank) {
    dict.insert(s);
  }

  if (dict.count(end) == 0) {
    return -1;
  }

  vector<string> choices{"A", "C", "G", "T"};
  queue<string> q;
  q.push(start);
  visited.insert(start);
  int count{0};
  while (!q.empty()) {
    int size = q.size();
    for (size_t i = 0; i < size; i++) {
      string str = q.front();
      q.pop();
      if (str == end) {
        return count;
      }

      for (size_t j = 0; j < str.length(); j++) {
        for (string ch : choices) {
          string tmp{str};
          tmp = tmp.replace(j, 1, ch);
          if (visited.count(tmp) == 0 && dict.count(tmp) == 0) {
            q.push(tmp);
            visited.insert(tmp);
          }
        }
      }
    }
    count++;
  }
  return -1;
}