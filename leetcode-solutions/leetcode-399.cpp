/*
 * Evaluate Division
 * 
 * You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.
 * You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.
 * 
 * Return the answers to all queries. If a single answer cannot be determined, return -1.0.
 * 
 * Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.
 * 
 */
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<string, vector<pair<string, double>>> adj;
unordered_map<string, int> vis;

bool dfs(string x, string d, double ans, double val, double &r, int &f) {
  if (vis.find(x) != vis.end()) return false;
  vis[x]++;
  ans *= val;
  if (x.compare(d) == 0) {
    r = ans;
    f = 1;
    return true;
  }
  for (auto v : adj[x])
    if (dfs(v.first, d, ans, v.second, r, f)) return true;

  return false;
}

vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values,
                            vector<vector<string>> &queries) {
  adj.clear();
  vis.clear();
  int n = equations.size();
  unordered_map<string, int> x;
  vector<double> res;
  for (int i = 0; i < n; i++) {
    auto u = equations[i];
    x[u[1]]++;
    x[u[0]]++;
    adj[u[0]].push_back({u[1], values[i]});
    adj[u[1]].push_back({u[0], (1 / values[i])});
  }
  for (auto u : queries) {
    auto s = u[0];
    auto d = u[1];
    vis.clear();
    if (x.find(s) == x.end() || x.find(d) == x.end()) {
      res.push_back(-1.0);
      continue;
    }
    double ans = 1.0, r = 1.0;
    int f = 0;
    dfs(s, d, ans, 1.0, r, f);
    if (f == 0)
      res.push_back(-1.0);
    else
      res.push_back(r);
  }
  return res;
}