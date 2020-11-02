#include <vector>
#include <algorithm>
using namespace std;

int maxArea(vector<int> &height)
{
    int ret{0};

    auto itrB = height.cbegin();
    auto itrE = height.cend() - 1;

    while (itrB != itrE)
    {
        int area = min(*itrB, *itrE) * distance(itrB, itrE);
        ret = max(ret, area);
        *itrB < *itrE ? ++itrB : --itrE;
    }

    return ret;
}