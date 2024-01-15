#include <algorithm>
#include <iostream>
#include <list>
using namespace std;

class AddValue {
 private:
  int theValue;

 public:
  AddValue(int v) : theValue(v) {}

  void operator()(int &elem) const { elem += theValue; }
};

int main() {
  list<int> coll;
  for (size_t i = 1; i <= 9; i++) {
    coll.push_back(i);
  }

  for_each(coll.begin(), coll.end(), AddValue(10));

  return 0;
}