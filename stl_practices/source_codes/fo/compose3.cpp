// fo/compose3.cpp

#include <algorithm>
#include <functional>
#include <iostream>
#include <locale>
#include <string>
using namespace std;
using namespace std::placeholders;

char myToupper(char c) {
  std::locale loc;
  return std::use_facet<std::ctype<char>>(loc).toupper(c);
}

int main() {
  string s("Internationalization");
  string sub("Nation");

  string::iterator pos = search(s.begin(), s.end(), sub.begin(), sub.end(),
                                bind(equal_to<char>(), bind(myToupper, _1), bind(myToupper, _2)));
  if (pos != s.end()) {
    cout << "\"" << sub << "\" is part of \"" << s << "\"" << endl;
  }
}