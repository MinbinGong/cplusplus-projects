/*
  Plus one

  You are given a large integer represented as an integer array digits,
  where each digits[i] is the ith digit of the integer.
  The digits are ordered from most significant to least significant in left-to-right order.
  The large integer does not contain any leading 0's.

  Increment the large integer by one and return the resulting array of digits.

  Approach
  Explanation:
  The function iterates through the digits in reverse order (j starts from the rightmost digit).

  If the current digit is less than 9, it means we can simply increment it and return the updated vector.
  The function exits at this point.

  If the current digit is 9, it is set to 0, and the loop continues to the next digit.

  If the loop completes without returning, it means all digits were 9,
  and a new digit '1' needs to be added at the beginning of the vector.

  A new vector num is initialized with the value '1'.

  The original digits are then appended to the num vector.

  The final result vector num is returned.
 */
#include <vector>
using namespace std;

vector<int> plusOne(vector<int>& digits) {
  for (int i = digits.size() - 1; i >= 0; --i) {
    if (digits[i] < 9) {
      digits[i]++;
      return digits;
    }

    digits[i] = 0;
  }

  vector<int> num;
  num.push_back(1);

  for (const int digit : digits) {
    num.push_back(digit);
  }
  return num;
}