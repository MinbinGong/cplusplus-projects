#include <algorithm>
#include <vector>
using namespace std;

void dfs(const vector<int>& nums, vector < int >> ::iterator start, vector<int>& path, vector<vector<int>>& res) {
  res.push_back(path);

  for (auto i = start; i < nums.end(); ++i) {
    if (i != start && *i == *(i - 1)) {
      continue;
    }

    path.push_back(*i);
    dfs(nums, i + 1, path, res);
    path.pop_back();
  }
}

vector<vector<int>> subsetWithDup(vector<int>& nums) {
  sort(nums.begin(), nums.end());

  vector<vector<int>> res;
  vector<int> path;

  dfs(nums, nums.begin(), path, res);
  return res;
}