// fo/sort1.cpp

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
using namespace std;

class Person {
 public:
  string firstname() const;
  string lastname() const;
};

class PersonSortCriterion {
 public:
  bool operator()(const Person& p1, const Person& p2) const {
    return p1.lastname() < p2.lastname() || (p1.lastname() == p2.lastname() && p1.firstname() < p2.firstname());
  }
};

int main() {
  set<Person, PersonSortCriterion> coll;

  // do something
  return 0;
}