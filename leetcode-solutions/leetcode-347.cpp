/*
 * Top K Frequent Elements
 * 
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
 * 
 * Example 1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 * 
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: [1]
 * 
 * Constraints:
 * 1 <= nums.length <= 105
 * k is in the range [1, the number of unique elements in the array].
 * It is guaranteed that the answer is unique.
 * 
 */

#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> topKFrequent(vector<int> &nums, int k) {
  unordered_map<int, int> freq;
  for (auto n : nums) freq[n]++;

  priority_queue<int, vector<int>, greater<int>()> myHeap;
  for (auto it = freq.cbegin(); it != freq.cend(); ++it) {
    myHeap.push(it->second);
    if (myHeap.size() > k) myHeap.pop();
  }

  vector<int> res;
  for (auto it = freq.cbegin(); it != freq.cend(); ++it)
    if (it->second > myHeap.top()) res.push_back(it->first);

  return res;                                                                                                             
}

vector<int> topKFrequent2(vector<int> &nums, int k) {
  if (nums.size() < k) {
    return {};
  }

  unordered_map<int, int> counts;
  int max_count = 0;
  for (const int num : nums) {
    max_count = max(max_count, ++counts[num]);
  }

  vector<vector<int>> buckets(max_count + 1);
  for (const auto &p : counts) {
    buckets[p.second].push_back(p.first);
  }

  vector<int> res;
  for (int i = max_count; i >= 0 && res.size() < k; i--) {
    for (const auto num : buckets[i]) {
      res.push_back(num);
      if (res.size() == k) {
        break;
      }
    }
  }

  return res;
}