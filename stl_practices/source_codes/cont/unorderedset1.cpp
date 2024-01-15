#include <iostream>
#include <numeric>
#include <unordered_set>
using namespace std;

int main() {
  unordered_set<int> coll{1, 2, 3, 5, 7, 11, 13, 17, 19, 77};
  for (const auto &e : coll) {
    cout << e << " ";
  }
  cout << endl;

  coll.insert({-7, 17, 33, -11, 17, 19, 1, 13});
  for (const auto &e : coll) {
    cout << e << " ";
  }
  cout << endl;

  coll.erase(33);

  coll.insert(accumulate(coll.begin(), coll.end(), 0));
  for (const auto &e : coll) {
    cout << e << " ";
  }
  cout << endl;

  if (coll.find(19) != coll.end()) {
    cout << "19 is available" << endl;
  }

  for (auto pos = coll.begin(); pos != coll.end();) {
    if (*pos < 0) {
      pos = coll.erase(pos);
    } else {
      ++pos;
    }
  }
  for (const auto &e : coll) {
    cout << e << " ";
  }
  cout << endl;

  return 0;
}