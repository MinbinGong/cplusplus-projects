// stl/deque1.cpp

#include <deque>
#include <iostream>
using namespace std;

int main() {
  deque<float> coll;

  // insert elements from 1.1 to 6.6 each at the front
  for (size_t i = 0; i < 6; i++) {
    coll.push_back(i * 1.1);
  }

  // print all elements followed by a space
  for (size_t i = 0; i < coll.size(); i++) {
    cout << coll[i] << ' ';
  }

  cout << endl;
  return 0;
}