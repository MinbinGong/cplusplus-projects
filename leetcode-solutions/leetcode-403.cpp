#include <unordered_map>
#include <unordered_set>
using namespace std;

bool jump(unordered_map<int, unordered_map<int, int>> &mp, unordered_set<int> &stset, int goalst, int pos, int k) {
  if (k == 0) return false;

  if (stset.count(pos) == 0 || pos > goalst) return false;

  if (goalst == pos) return true;

  if (mp.count(pos) && mp[pos].count(k)) return mp[pos][k];

  bool success = jump(mp, stset, goalst, pos + k - 1, k - 1) || jump(mp, stset, goalst, pos + k, k) ||
                 jump(mp, stset, goalst, pos + k + 1, k + 1);

  return mp[pos][k] = success;
}

bool canCross(vector<int> &stones) {
  if (stones.at(0) + 1 != stones.at(1)) return false;

  unordered_map<int, unordered_map<int, int>> mp;
  unordered_set<int> stset;

  for (auto &stone : stones) stset.insert(stone);

  int goalst = stones.back();

  return jump(mp, stset, goalst, stones.at(1), 1);
}