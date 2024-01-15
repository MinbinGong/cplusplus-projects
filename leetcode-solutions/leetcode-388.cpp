#include <string>
#include <vector>
using namespace std;

int lengthLongestPath(string input) {
  int maxLen = 0;
  vector<int> levels;
  int n = input.size();
  for (int i = 0; i < n; i++) {
    int level = 0;
    while (input[i] == '\t') {
      level++;
      i++;
    }
    if (level >= levels.size()) levels.resize(level + 1, 0);
    levels[level] = 0;
    bool isFile = false;
    while (i < n && input[i] != '\n') {
      levels[level]++;
      if (input[i] == '.') isFile = true;
      i++;
    }
    if (!isFile) continue;
    int sum = level;
    for (int j = 0; j <= level; j++) sum += levels[j];
    if (maxLen < sum) maxLen = sum;
  }
  return maxLen;
}
