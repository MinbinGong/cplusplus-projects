// fo/sequence1.cpp

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>

#include "..\print.hpp"
using namespace std;

class IntSequence {
 private:
  int value;

 public:
  IntSequence(int initialValue) : value(initialValue) {}

  int operator()() { return ++value; }
};

int main() {
  list<int> coll;

  generate_n(back_inserter(coll), 9, IntSequence(1));

  PRINT_ELEMENTS(coll);

  generate(next(coll.begin()), prev(coll.end()), IntSequence(42));

  PRINT_ELEMENTS(coll);
}