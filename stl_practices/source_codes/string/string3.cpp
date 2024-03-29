// string/string3.cpp

#include <algorithm>
#include <iostream>
#include <iterator>
#include <locale>
#include <string>
using namespace std;

int main() {
  string input;
  cin.unsetf(ios::skipws);

  const locale& loc(cin.getloc());
  unique_copy(istream_iterator<char>(cin), istream_iterator<char>(), back_inserter(input),
              [=](char c1, char c2) { return isspace(c1, loc) && isspace(c2, loc); });
  cout << input;
}