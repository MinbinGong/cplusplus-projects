#include <string>
using namespace std;

char findTheDifference(string s, string t) {
  int temp = 0;
  for (char c : t) temp += c - 'a';
  for (char c : s) temp -= c - 'a';
  return temp + 'a';
}