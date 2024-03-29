// regex/regex2.cpp

#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

int main() {
  string data = "XML tag: <tag-name>the value</tag-name>.";
  cout << "data: " << data << "\n\n";

  smatch m;
  bool found = regex_search(data, m, regex("<(.*)>(.*)</(\\1)>"));

  // print match details;
  cout << "m.empty(): " << boolalpha << m.empty() << endl;
  cout << "m.size(): " << m.size() << endl;

  if (found) {
    cout << "m.str(): " << m.str() << endl;
    cout << "m.length(): " << m.length() << endl;
    cout << "m.position(): " << m.position() << endl;
    cout << "m.prefix().str(): " << m.prefix().str() << endl;
    cout << "m.suffix().str(): " << m.suffix().str() << endl;
    cout << endl;

    // iterating over all matches (using the match index);
    for (size_t i = 0; i < m.size(); i++) {
      cout << "m[" << i << "].str(): " << m[i].str() << endl;
      cout << "m.str(" << i << "): " << m.str(i) << endl;
      cout << "m.position(" << i << "): " << m.position(i) << endl;
    }
    cout << endl;

    // iterating over all matches (using iterators);
    cout << "matches:" << endl;
    for (auto pos = m.begin(); pos != m.end(); ++pos) {
      cout << " " << *pos << " ";
      cout << "(length: " << pos->length() << ")" << endl;
    }
  }
}