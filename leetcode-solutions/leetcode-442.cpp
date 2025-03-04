#include <vector>
using namespace std;

vector<int> findDuplicates(vector<int> &nums) {
  vector<int> ans{};
  for (size_t i = 0; i < nums.size(); i++) {
    nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1];
    if (nums[abs(nums[i]) - 1] > 0) {
      ans.push_back(abs(nums[i]));
    }
  }
  return ans;
}