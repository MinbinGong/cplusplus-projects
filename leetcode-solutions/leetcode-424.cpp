/*
 * Maintain a window that slides down the string. In each iteration, we move the "end" of the window down one step. Use
 * a vector to record the number of every letter within the window, and maintain the number of the most letter in the
 * window. The window length minus the number of the most letter is the minimum number of operations we need to convert
 * all the letters in the window to the same letter. Therefore, when the minimum number of operations surpasses "k", we
 * need to shrink the window by moving the "start" of the window down one step. Now the window length is the length of
 * the substring composed of the same letter that we can get. Slide the window all the way down the whole string and
 * record the maximum window length during the process.
 */

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int characterReplacement(string s, int k) {
  vector<int> letterCount(26, 0);
  int maxLen = 0, start = 0, end = 0, mostLetter = 0;
  while (end < s.size()) {
    letterCount[s[end] - 'A']++;
    mostLetter = max(mostLetter, letterCount[s[end] - 'A']);
    if (end - start + 1 - mostLetter > k) {
      letterCount[s[start] - 'A']--;
      start++;
    }
    maxLen = max(maxLen, end - start + 1);
    end++;
  }
  return maxLen;
}