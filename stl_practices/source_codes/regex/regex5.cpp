// regex/regex5.cpp

#include <iostream>
#include <regex>

#include "regexexception.hpp"
using namespace std;

int main() {
  try {
    // initialize regular expression with invalid syntax
    regex pat("\\\\.*index\\f{([^}]*)\\}", regex_constants::grep | regex_constants::icase);
  } catch (const regex_error& e) {
    cerr << "regex error: \n"
         << " what(): " << e.what() << "\n"
         << " code(): " << regexCode(e.code()) << endl;
  }
}