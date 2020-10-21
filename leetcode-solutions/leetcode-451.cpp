#include <string>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

string frequencySort(string s)
{
    vector<pair<int, int>> count(256);
    for (size_t i = 0; i < s.length(); i++)
    {
        count[s[i]].first++;
    }

    for (size_t i = 0; i < 256; i++)
    {
        count[i].second = i;
    }

    sort(count.begin(), count.end(), greater<pair<int, int>>());

    string result;
    for (size_t i = 0; i < count.size(); i++)
    {
        result += string(count[i].first, count[i].second);
    }
    return result;
}