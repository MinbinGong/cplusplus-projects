/*
 * Reverse Words in a String
 *
 * Given an input string s, reverse the order of the words.
 *
 * A word is defined as a sequence of non-space characters. The words in s will
 * be separated by at least one space.
 *
 * Return a string of the words in reverse order concatenated by a single
 * space.
 *
 * Note that s may contain leading or trailing spaces or multiple spaces
 * between two words. The returned string should only have a single space
 * separating the words. Do not include any extra spaces.
 *
 */
#include <string>
#include <algorithm>
using namespace std;

void reverse_string(string &s, int i, int j) {
  while (i <= j) {
    swap(s[i], s[j]);
    i++;
    j--;
  }
}

string reverse_words(string s) {
  int n = s.size();

  reverse_string(s, 0, n - 1);
  
  int i = 0;
  for (int j = 0; j < n; j++) {
    if (s[j] == ' ') {
      reverse_string(s, i, j - 1);
      i = j+1;
    }

    if (j == n - 1) {
      reverse_string(s, i, j);
    }

  }

  int p = 0, flag = 0;
  i = n - 1;
  while (i >= 0 && s[i] == ' ') {
    i--;
  }

  int last = i;

  i = 0;
  while (i < n && s[i] == ' ') {
    i++;
  }

  while (i <= last) {
    if (s[i] !=  ' ') {
      s[p++] = s[i];
      flag = true;
    }

    if (s[i] == ' ' && flag) {
      s[p++] = ' ';
      flag = false;
    }

    i++;
  }

  s.resize(p);
  return s;
}
