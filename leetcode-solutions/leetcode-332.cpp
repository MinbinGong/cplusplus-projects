/*
  Reconstruct Itinerary

  题目描述
  给定一个人坐过的一些飞机的起止机场，已知这个人从 JFK 起飞，那么这个人是按什么顺序
  飞的；如果存在多种可能性，返回字母序最小的那种。

  题解
  本题可以先用哈希表记录起止机场，其中键是起始机场，值是一个多重集合，表示对应的终
  止机场。因为一个人可能坐过重复的线路，所以我们需要使用多重集合储存重复值。储存完成之
  后，我们可以利用栈来恢复从终点到起点飞行的顺序，再将结果逆序得到从起点到终点的顺序。
 */

#include <algorithm>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<string> findItinerary(vector<vector<string>> &tickets) {
  if (tickets.empty()) {
    return {};
  }

  unordered_map<string, multiset<string>> graph;
  for (auto ticket : tickets) {
    graph[ticket[0]].insert(ticket[1]);
  }
  vector<string> res;
  stack<string> q;
  q.push("JFK");
  while (!q.empty()) {
    auto from = q.top();
    if (!graph[from].size()) {
      res.push_back(from);
      q.pop();
    } else {
      auto to = graph[from].begin();
      q.push(*to);
      graph[from].erase(to);
    }
  }
  reverse(res.begin(), res.end());
  return res;
}

bool dfs(unordered_map<string, vector<string>> &m, string cur, vector<string> &res, size_t size) {
  if (res.size() == size) return true;
  for (auto &next : m[cur]) {
    if (next.size() != 3) continue;
    res.push_back(next);
    string tmp = next;
    next += '.';
    if (dfs(m, tmp, res, size)) return true;
    res.pop_back();
    next.pop_back();
  }
  return false;
}

vector<string> findItinerary1(vector<vector<string>> &tickets) {
  unordered_map<string, vector<string>> m;
  for (const auto &v : tickets) m[v[0]].push_back(v[1]);
  for (auto &[_, v] : m) sort(v.begin(), v.end());
  vector<string> res{"JFK"};
  dfs(m, "JFK", res, tickets.size() + 1);
  return res;
}
