// algo/count1.cpp

#include "algostuff.hpp"
using namespace std;

int main() {
  vector<int> coll;
  int num;
  INSERT_ELEMENTS(coll, 1, 9);
  PRINT_ELEMENTS(coll);

  num = count(coll.cbegin(), coll.cend(), 4);
  cout << "Number of elements equal to 4: " << num << endl;

  num = count_if(coll.cbegin(), coll.cend(), [](int elem) { return elem % 2 == 0; });
  cout << "Number of elements with even value: " << num << endl;

  num = count_if(coll.cbegin(), coll.cend(), [](int elem) { return elem > 4; });
  cout << "Number of elements greater than 4: " << num << endl;
}