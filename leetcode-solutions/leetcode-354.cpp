#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

int help(vector<pair<int, int>> &envelopes)
{
    sort(envelopes.begin(), envelopes.end(), [](auto &p1, auto &p2) {
        return p1.first < p2.first || (p1.first == p2.first && p1.second > p2.second);
    });

    vector<int> col;
    for (auto &pair : envelopes)
    {
        auto it = lower_bound(col.begin(), col.end(), pair.second);
        if (it == col.end())
            col.push_back(pair.second);
        else if (*it > pair.second)
            *it = pair.second;
    }
    return col.size();
}

int maxEnvelopes(vector<vector<int>> &envelopes)
{
    vector<pair<int, int>> src{};
    for (size_t i = 0; i < envelopes.size(); ++i)
        src.emplace_back(std::make_pair(envelopes[i][0], envelopes[i][1]));

    return help(src);
}