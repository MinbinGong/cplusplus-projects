#include <vector>
using namespace std;

int findMajority(vector<int> &nums) {
  int count = 0;
  int candidate = 0;

  for (auto num : nums) {
    if (0 == count) {
      candidate = num;
    }

    if (candidate == num) {
      count++;
    } else {
      count--;
    }
  }
  return candidate;
}