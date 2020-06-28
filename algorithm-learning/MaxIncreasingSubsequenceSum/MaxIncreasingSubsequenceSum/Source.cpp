#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int sum(const vector<int>& src);
int maxIncreasingSubsequence(const vector<int>& src);

int main()
{
    vector<int> inVec{ 1, 101, 2, 3, 100, 4, 5 };
    
    cout << "Max increasing subsequence sum : " << maxIncreasingSubsequence(inVec) << endl;
    return 0;
}

int sum(const vector<int>& src)
{
    int ret = 0;
    for (auto it : src)
    {
        ret += it;
    }
    return ret;
}

int maxIncreasingSubsequence(const vector<int>& src)
{
    vector<vector<int>> tmpVec;

    auto it = src.cbegin();
    while (it != src.cend())
    {
        int tmp = *it;
        vector<int> subsequence;

        subsequence.emplace_back(tmp);
        for (auto itr = it; itr != src.cend(); )
        {
            if (*(++itr) > tmp)
            {
                tmp = *itr;
                subsequence.emplace_back(tmp);
            }
            else
            {
                itr++;
            }
        }

        tmpVec.emplace_back(subsequence);
        it++;
    }

    int ret = 0;
    for (auto itr = tmpVec.cbegin(); itr != tmpVec.cend(); ++itr)
    {
        int tmp = sum(*itr);
        if (ret < tmp)
        {
            ret = tmp;
        }
    }
    return ret;
}
