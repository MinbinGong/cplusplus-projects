#include <set>
#include <vector>

int findKthLargest(std::vector<int>& nums, int k) {
  std::multiset<int> s;
  for (const auto i : nums) {
    s.insert(i);
  }

  long long counter{0};
  int ret{0};
  for (const auto i = s.rbegin(); i != s.rend(); ++i) {
    counter++;
    if (counter == k) {
      ret = *i;
      break;
    }
  }

  return ret;
}
