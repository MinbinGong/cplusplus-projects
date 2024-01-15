/*
 * Given a non-empty array of integers, every element appears three times except for one,
 * which appears exactly once.
 * Find that single one.
 */

#include <vector>
using namespace std;

int singleNumber(vector<int> &A) {
  if (A.size() == 0) {
    return 0;
  }

  int first = 0, second = 0;
  int szA = A.size();
  for (int i = 0; i < szA; i++) {
    second |= (first & A[i]);
    first ^= A[i];
    int check = ~(first & second);
    first &= check;
    second &= check;
  }
  return first;
}