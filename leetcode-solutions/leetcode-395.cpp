#include <string>
#include <vector>
using namespace std;

int longestSubstring(string s, int k)
{
    vector<int> vocab(26, 0);
    for (auto ch : s)
    {
        ++vocab[ch - 'a'];
    }
    vector<int> cands;
    for (int i = 0; i < s.size(); ++i)
    {
        if (vocab[s[i] - 'a'] < k)
        {
            cands.emplace_back(i);
        }
    }
    if (cands.empty())
        return s.size();
    cands.emplace_back(s.size());
    int start = 0;
    int longest = 0;
    for (auto cand : cands)
    {
        if (cand - start >= k)
        {
            longest = max(longestSubstring(s.substr(start, cand - start), k), longest);
        }
        start = cand + 1;
    }
    return longest;
}