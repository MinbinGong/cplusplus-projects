/*
 * 457. Circular Array Loop
 *
 * You are given a circular array nums of positive and negative integers. If a number k at an index is positive, then move forward k steps. Conversely, if it's negative (-k), move backward k steps. Since the array is circular, you may assume that the last element's next element is the first element, and the first element's previous element is the last element.
 *
 * Determine if there is a loop (or a cycle) in nums. A cycle must start and end at the same index and the cycle's length > 1. Furthermore, movements in a cycle must all follow a single direction. In other words, a cycle must not consist of both forward and backward movements.
 *
 * Constraints:
 * -1000 <= nums[i] <= 1000
 * nums[i] != 0
 * 1 <= nums.length <= 5000
 * 
 */
#include <vector>
using namespace std;

bool circularArrayLoop(vector<int> &nums) {
  int id = 1001, MAX = 1000, n = nums.size();

  for (size_t i = 0; i < n; i++) {
    if (nums[i] > MAX) {
      continue;
    }

    bool positive = (nums[i] > 0);
    int j = i;
    while (true) {
      if (nums[j] == id) {
        return true;
      }

      if ((positive && nums[j] < 0) || (!positive && nums[j] > 0)) {
        break;
      }

      if (nums[j] > MAX) {
        break;
      }

      int jj = j;
      j = (j + nums[j] % n + n) % n;
      if (jj == j) {
        break;
      }

      nums[jj] = id;
    }
    id++;
  }
  return false;
}