#include <string>
#include <vector>
using namespace std;

string originalDigits(string s) {
  vector<int> alphaCount(256, 0);
  for (int i = 0; i < s.size(); i++) {
    alphaCount[s[i]]++;
  }
  vector<int> numBin(10, 0);
  string numStr[] = {"zero", "eight", "three", "two", "four", "five", "seven", "one", "six", "nine"};
  char specChar[] = {'z', 'g', 'h', 't', 'r', 'f', 'v', 'o', 'x', 'i'};
  int numOrder[] = {0, 8, 3, 2, 4, 5, 7, 1, 6, 9};
  for (int i = 0; i < 10; i++) {
    int num = numOrder[i];
    string &s = numStr[i];
    char c = specChar[i];
    int count = alphaCount[c];
    numBin[num] += count;
    for (int i = 0; i < s.size(); i++) {
      alphaCount[s[i]] -= count;
    }
  }
  string ret;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < numBin[i]; j++) {
      ret += ('0' + i);
    }
  }
  return ret;
}
