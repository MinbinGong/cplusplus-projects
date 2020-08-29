#include <vector>
#include <utility>
using namespace std;

int maxRotateFunction(vector<int> &a)
{
    if (a.empty())
        return 0;

    long long sum = 0;
    long tmp = 0;
    for (int i = 0; i < a.size(); i++)
    {
        sum += a[i];
        tmp += (i * a[i]);
    }
    long ans = tmp;
    for (int i = a.size() - 1; i >= 0; i--)
    {
        tmp -= ((a.size() - 1) * a[i]);
        tmp += (sum - a[i]);
        ans = max(ans, tmp);
    }
    return ans;
}