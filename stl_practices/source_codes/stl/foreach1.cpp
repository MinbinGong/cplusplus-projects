#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void print(int elem) { cout << elem << ' '; }

int main() {
  vector<int> coll;
  for (size_t i = 0; i < 9; i++) {
    coll.push_back(i);
  }

  for_each(coll.cbegin(), coll.cend(), print);
  cout << endl;

  return 0;
}