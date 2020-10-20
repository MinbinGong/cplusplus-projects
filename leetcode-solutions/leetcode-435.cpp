#include <vector>
#include <algorithm>
using namespace std;

int eraseOverlapIntervals(vector<vector<int>> &intervals)
{
    if (intervals.empty())
    {
        return 0;
    }

    int ans{-1};
    sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
        return a[1] < b[1];
    });

    vector<int> prev{intervals[0]};
    for (const auto &i : intervals)
    {
        if (prev[1] > i[0])
        {
            ans++;
        }
        else
        {
            prev = i;
        }
    }
    return ans;
}