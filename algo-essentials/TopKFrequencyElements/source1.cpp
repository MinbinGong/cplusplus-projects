#include <functional>
#include <map>
#include <unordered_map>
#include <vector>

std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
  std::unordered_map<int, int> map;
  for (const auto& x : nums) {
    map[x]++;
  }

  std::multimap<int, int, std::greater<int>> map2;
  for (const auto& it : map) {
    map2.insert({it.second, it.first});
  }

  std::vector<int> ans;
  int count = 0;
  for (const auto& temp : map2) {
    count++;
    if (count > k) {
      return ans;
    }
    ans.push_back(temp.second);
  }
  return ans;
}