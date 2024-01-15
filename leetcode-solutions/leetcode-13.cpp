#include <map>
#include <string>
using namespace std;

int romanToInt(string s) {
  int sum{0};
  if (s.empty()) return sum;

  string srcStr{s};
  map<string, int> dict1 = {{"CM", 900}, {"CD", 400}, {"XC", 90}, {"XL", 40}, {"IX", 9}, {"IV", 4}};
  for (auto const &e : dict1) {
    auto it = srcStr.find(e.first);
    if (it != string::npos) {
      srcStr.erase(it, 2);
      sum += e.second;
    }
  }

  for (auto const &e : srcStr) {
    if (e == 'M')
      sum += 1000;
    else if (e == 'D')
      sum += 500;
    else if (e == 'C')
      sum += 100;
    else if (e == 'L')
      sum += 50;
    else if (e == 'X')
      sum += 10;
    else if (e == 'V')
      sum += 5;
    else
      sum += 1;
  }

  return sum;
}