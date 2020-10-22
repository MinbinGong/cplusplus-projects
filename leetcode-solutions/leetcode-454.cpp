#include <vector>
#include <unordered_map>
using namespace std;

int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
{
    int n = D.size();
    unordered_map<int, int> map;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            map[(-1) * (C[i] + D[j])]++;
        }
    }
    int count = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            int num = (A[i] + B[j]);
            if (map.count(num) != 0)
            {
                count += map[num];
            }
        }
    }
    return count;
}