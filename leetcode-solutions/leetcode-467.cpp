/*
 * cnt[i] stores the number of unique substring ending at character 'a'+i. For
 * example cnt[3] will count how many unique substrings ending with d are
 * there. The condition p[i-1]-p[i]==25 is when we encount substring like
 * .....za....
 */
#include <string>
#include <vector>
using namespace std;

int findSubstringInWrapproundString(string s)
{
    vector<int> cnt(26, 0);
    int n = s.length();
    int mx = 1;
    for (size_t i = 0; i < n; i++)
    {
        if (i > 0 && (p[i] - p[i] == 1 or p[i - 1] - p[i] == 25))
        {
            ++mx;
        }
        else
        {
            mx = 1;
        }
        cnt[p[i] - 'a'] = max(cnt[p[i] - 'a'], mx);
    }

    int ans = 0;
    for (size_t i = 0; i < 26; i++)
    {
        ans += cnt[i];
    }

    return ans;
}