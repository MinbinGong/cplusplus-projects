#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

vector<int> topKFrequent(vector<int> &nums, int k)
{
    unordered_map<int, int> freq;
    for (auto n : nums)
        freq[n]++;

    priority_queue<int, vector<int>, greater<int>> myHeap;
    for (auto it = freq.cbegin(); it != freq.cend(); ++it)
    {
        myHeap.push(it->second);
        if (myHeap.size() > k)
            myHeap.pop();
    }

    vector<int> res;
    for (auto it = freq.cbegin(); it != freq.cend(); ++it)
        if (it->second > myHeap.top())
            res.push_back(it->first);

    return res;
}