#include <string>
#include <vector>
using namespace std;

int firstUniqChar(string s)
{
    vector<int> cnt(26, 0);
    vector<int> lastpos(26, 0);
    for (int i = 0; i < s.size(); ++i)
    {
        ++cnt[s[i] - 'a'];
        lastpos[s[i] - 'a'] = i;
    }

    int res = s.size();
    for (char c = 0; c < 26; ++c)
        if (cnt[c] == 1 && res > lastpos[c])
            res = lastpos[c];

    return (res == s.size()) ? -1 : res;
}