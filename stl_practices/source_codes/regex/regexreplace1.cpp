// regex/regexreplace1.cpp

#include <iostream>
#include <iterator>
#include <regex>
#include <string>
using namespace std;

int main() {
  string data =
    "<person>\n"
    " <first>Nico</first>\n"
    " <last>Josutties</last>\n"
    "</person>\n";
  regex reg("<(.*)>(.*)</(\\1)>");

  // print data with replacement for matched patterns
  cout << regex_replace(data, reg, "<$1 value=\"$2\"/>") << endl;

  // same using sed syntax
  cout << regex_replace(data, reg, "<\\1 value=\"\\2\"/>", regex_constants::format_sed) << endl;

  // use iterator interface, and
  // - format_no_copy: don't copy characters that don't match
  // - format_first_only: replace only the first match found
  string res2;
  regex_replace(back_inserter(res2), data.begin(), data.end(), reg, "<$1 value=\"$2\"/>",
                regex_constants::format_no_copy | regex_constants::format_first_only);
  cout << res2 << endl;
}