#include <vector>
int findDuplicate(std::vector<int> &nums) {
  int n = nums.size();
  if (n == 0) return -1;

  int slow = 0, fast = 0;
  while (1) {
    slow = nums[slow];
    fast = nums[nums[fast]];
    if (slow == fast) break;
  }

  slow = 0;
  while (1) {
    slow = nums[slow];
    fast = nums[fast];
    if (slow == fast) return fast;
  }

  return -1;
}