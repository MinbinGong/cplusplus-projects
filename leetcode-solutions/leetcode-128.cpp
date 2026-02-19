/*
 * Longest Consecutive Sequence
 * Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
 *
 * You must write an algorithm that runs in O(n) time.
 */
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <utility>
using namespace std;

int longestConsecutive(vector<int>& nums) {
  unordered_set<int> hash;
  for (const int& num : nums) {
    hash.insert(num);
  }

  int ans = 0;
  while (!hash.empty()) {
    int cur = *(hash.begin());
    hash.erase(cur);
    int next = cur + 1, prev = cur - 1;
    while (hash.count(next)) {
      hash.erase(next++);
    }
    while (hash.count(prev)) {
      hash.erase(prev--);
    }
    ans = max(ans, next - prev - 1);
  }
  return ans;
}