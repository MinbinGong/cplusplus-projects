// stl/reviter1.cpp

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int main() {
  vector<int> coll;

  for (int i = 1; i <= 9; i++) {
    coll.push_back(i);
  }

  copy(coll.crbegin(), coll.crend(), ostream_iterator<int>(cout, " "));
  cout << endl;
}