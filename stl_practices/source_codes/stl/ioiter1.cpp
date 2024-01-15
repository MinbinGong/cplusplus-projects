#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

int main() {
  vector<string> coll;

  copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(coll));

  sort(coll.begin(), coll.end());

  unique_copy(coll.cbegin(), coll.cend(), ostream_iterator<string>(cout, "\n"));

  return 0;
}