#include <vector>
using namespace std;

int minPatches(vector<int> &nums, int n) {
  int szNums = nums.size();
  unsigned int farNum = 0;
  int idx = 0, padding = 0;

  while (farNum < n) {
    if (idx < szNums && nums[idx] <= farNum + 1) {
      farNum += nums[idx++];
    } else {
      padding++;
      farNum = farNum * 2 + 1;
    }
  }
  return padding;
}