#include <vector>
using namespace std;

vector<int> findDisappearedNumbers(vector<int> &nums)
{
    int n = nums.size();

    for (size_t i = 0; i < n; i++)
    {
        while (nums[i] != i + 1)
        {
            if (nums[i] != nums[nums[i] - 1])
            {
                swap(nums[i], nums[nums[i] - 1]);
            }
            else
            {
                break;
            }
        }
    }

    vector<int> res;
    for (size_t i = 0; i < n; i++)
    {
        if (nums[i] != i + 1)
        {
            res.push_back(i + 1);
        }
    }

    return res;
}