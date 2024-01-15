#include <iostream>
#include <set>
using namespace std;

class RuntimeCmp {
 public:
  enum cmp_mode { normal, reverse };

 private:
  cmp_mode mode;

 public:
  RuntimeCmp(cmp_mode m = normal) : mode(m) {}

  template <typename T>
  bool operator()(const T &t1, const T &t2) const {
    return mode == normal ? t1 < t2 : t2 < t1;
  }
  bool operator==(const RuntimeCmp &rc) const { return mode == rc.mode; }
};

using IntSet = set<int, RuntimeCmp>;

int main() {
  IntSet coll1 = {4, 7, 5, 1, 6, 2, 5};

  RuntimeCmp reverse_order(RuntimeCmp::reverse);

  IntSet coll2(reverse_order);
  coll2 = {4, 7, 5, 1, 6, 2, 5};

  coll1 = coll2;
  coll1.insert(3);

  return;
}