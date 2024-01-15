#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int thirdMax(vector<int> &nums) {
  set<int> num(nums.begin(), nums.end());
  if (num.size() < 3) return *(num.rbegin());
  auto it = num.rbegin();
  advance(it, 2);
  return *it;
}