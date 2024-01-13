#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

vector<string> findItinerary(vector<vector<string>> &tickets)
{
    unordered_map<string, multiset<string>> graph;
    for (auto ticket : tickets)
    {
        graph[ticket[0]].insert(ticket[1]);
    }
    vector<string> res;
    stack<string> q;
    q.push("JFK");
    while (!q.empty())
    {
        auto from = q.top();
        if (!graph[from].size())
        {
            res.push_back(from);
            q.pop();
        }
        else
        {
            auto to = graph[from].begin();
            q.push(*to);
            graph[from].erase(to);
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

bool dfs(unordered_map<string, vector<string>> &m, string cur, vector<string> &res, size_t size)
{
    if (res.size() == size)
        return true;
    for (auto &next : m[cur])
    {
        if (next.size() != 3)
            continue;
        res.push_back(next);
        string tmp = next;
        next += '.';
        if (dfs(m, tmp, res, size))
            return true;
        res.pop_back();
        next.pop_back();
    }
    return false;
}

vector<string> findItinerary1(vector<vector<string>> &tickets)
{
    unordered_map<string, vector<string>> m;
    for (const auto &v : tickets)
        m[v[0]].push_back(v[1]);
    for (auto &[_, v] : m)
        sort(v.begin(), v.end());
    vector<string> res{"JFK"};
    dfs(m, "JFK", res, tickets.size() + 1);
    return res;
}

