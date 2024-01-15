#include <algorithm>
#include <string>
#include <vector>

std::string largestNumber(std::vector<int>& nums) {
  if (std::count(nums.begin(), nums.end(), 0) == nums.size()) {
    return "0";
  }

  std::sort(nums.begin(), nums.end(), [](int a, int b) {
    std::string at = std::to_string(a);
    std::string bt = std::to_string(b);
    return at + bt >= bt + at;
  });

  std::string res;
  for (const auto it : nums) {
    res += std::to_string(it);
  }

  return res;
}