#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
  sort(people.begin(), people.end(),
       [](vector<int> &a, vector<int> &b) { return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]); });
  vector<vector<int>> ans;
  for (auto &p : people) ans.insert(ans.begin() + p[1], p);
  return ans;
}