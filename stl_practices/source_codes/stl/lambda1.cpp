#include <algorithm>
#include <deque>
#include <iostream>
using namespace std;

int main() {
  deque<int> coll{1, 3, 19, 5, 13, 7, 11, 2, 17};

  int x{5}, y{12};
  auto pos = find_if(coll.cbegin(), coll.cend(), [=](int i) { return i > x && i < y; });

  cout << "First element > 5 and < 12 : " << *pos << endl;

  return 0;
}