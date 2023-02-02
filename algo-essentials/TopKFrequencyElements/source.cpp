#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<int> topKFrequent(std::vector<int>& nums, int k)
{
    std::unordered_map<int, int> freq;
    int maxFreq = 0;
    for (auto const elem : nums)
    {
        freq[elem]++;
        maxFreq = std::max(maxFreq, freq[elem]);
    }

    std::vector<std::vector<int>> vals(maxFreq + 1);
    for (auto it = freq.cbegin(); it != freq.cend(); it++)
    {
        vals[it->second].push_back(it->first);
    }

    int it = maxFreq;
    std::vector<int> res;
    while (k > 0)
    {
        if (vals[it].size() == 0)
        {
            it--;
            continue;
        }

        res.push_back(vals[i][vals[it].size() - 1]);
        vals[it].pop_back();
        k--;
    }

    return res;
}