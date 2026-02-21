/*
 * Longest Absolute File Path
 * 
 * Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
 * Output: 20
 * Explanation: We have only one file, and the absolute path is "dir/subdir2/file.ext" of length 20.
 * 
 * Input: input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
 * Output: 32
 * Explanation: We have two files:
 * "dir/subdir1/file1.ext" of length 21
 * "dir/subdir2/subsubdir2/file2.ext" of length 32.
 * We return 32 since it is the longest absolute path to a file.
 * 
 * Constraints:
 * 1 <= input.length <= 10^4
 * input may contain lowercase or uppercase English letters, a new line character '\n', a tab character '\t', a dot '.', a space ' ', and digits.
 * 
 */
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
