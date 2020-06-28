#include <iostream>
#include <vector>
using namespace std;

int trap_water(vector<int> &height);

int main()
{
    vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    cout << trap_water(height) << endl;

    return 0;
}

int trap_water(vector<int> &height)
{
    int left_max = 0, right_max = 0, ret = 0;

    int low = 0, high = height.size() - 1;
    while (low <= high)
    {
        if (height[low] < height[high])
        {
            if (height[low] > left_max)
            {
                left_max = height[low];
            }
            else
            {
                ret += left_max - height[low];
            }
            low++;
        }
        else
        {
            if (height[high] > right_max)
            {
                right_max = height[high];
            }
            else
            {
                ret += right_max - height[high];
            }
            high--;
        }
    }
    return ret;
}