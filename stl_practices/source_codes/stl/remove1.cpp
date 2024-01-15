#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

int main() {
  list<int> coll;
  for (size_t i = 1; i <= 6; i++) {
    coll.push_back(i);
    coll.push_front(i);
  }

  cout << "Pre: ";
  copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
  cout << endl;

  auto end = remove(coll.begin(), coll.end(), 3);

  cout << "Post: ";
  copy(coll.begin(), end, ostream_iterator<int>(cout, " "));
  cout << endl;

  cout << "number of removed elements: " << distance(end, coll.end()) << endl;

  coll.erase(end, coll.end());

  copy(coll.begin(), end, ostream_iterator<int>(cout, " "));
  cout << endl;

  return 0;
}