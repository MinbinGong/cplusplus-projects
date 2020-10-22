#include <vector>
#include <algorithm>
using namespace std;

int findContentChildren(vector<int> &g, vector<int> &s)
{
    int gSz = g.size();
    int sSz = s.size();
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int i = 0, j = 0, ans = 0;
    while (i < gSz && j < sSz)
    {
        if (s[j] >= g[i])
        {
            ans++;
            i++;
        }
        j++;
    }
    return ans;
}