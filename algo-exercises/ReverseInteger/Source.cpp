#include <iostream>
using namespace std;

int reverse(int x) {
  int ret = 0;
  while (x != 0) {
    ret = x % 10 + ret * 10;
    x /= 10;
  }
  return ret;
}

int main() {
  int a{123}, b{-123}, c{120} /*, d{ 123412341234125 }*/;

  cout << reverse(a) << endl << reverse(b) << endl << reverse(c) << endl /* << reverse(d) << endl*/;

  return 0;
}