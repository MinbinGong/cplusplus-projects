#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

void printLists(const list<int> &l1, const list<int> &l2) {
  cout << "list1: ";
  copy(l1.cbegin(), l1.cend(), ostream_iterator<int>(cout, " "));
  cout << endl;
  cout << "list2: ";
  copy(l2.cbegin(), l2.cend(), ostream_iterator<int>(cout, " "));
  cout << endl << endl;
}

int main() {
  list<int> list1, list2;
  for (size_t i = 0; i < 6; i++) {
    list1.push_back(i);
    list2.push_front(i);
  }
  printLists(list1, list2);

  list2.splice(find(list2.begin(), list2.end(), 3), list1);
  printLists(list1, list2);

  list2.splice(list2.end(), list2, list2.begin());
  printLists(list1, list1);

  list2.sort();
  list1 = list2;
  list2.unique();
  printLists(list1, list2);

  list1.merge(list2);
  printLists(list1, list2);
}