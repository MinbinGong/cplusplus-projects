#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
{
    priority_queue<pair<int, pair<int, int>>> mxheap;
    for (auto x : nums1)
    {
        for (auto y : nums2)
        {
            if (mxheap.size() >= k)
            {
                if (mxheap.top().first > (x + y))
                {
                    mxheap.pop();
                    mxheap.push({x + y, {x, y}});
                }
            }
            else
                mxheap.push({x + y, {x, y}});
        }
    }
    vector<vector<int>> res;
    while (mxheap.size() != NULL)
    {
        auto x = mxheap.top();
        mxheap.pop();
        res.push_back({x.second.first, x.second.second});
    }
    //reverse(res.begin(),res.end());
    return res;
}