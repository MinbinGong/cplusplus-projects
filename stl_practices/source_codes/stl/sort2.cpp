// stl/sort2.cpp

#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
using namespace std;

class Person {
 public:
  string firstname() const;
  string lastname() const;
};

int main() {
  deque<Person> coll;

  sort(coll.begin(), coll.end(), [](const Person& p1, const Person& p2) {
    return p1.lastname() < p2.lastname() || (p1.lastname() == p2.lastname() && p1.firstname() < p2.firstname());
  });
  return 0;
}