#include <vector>
using namespace std;

bool circularArrayLoop(vector<int> &nums)
{
    int id = 1001, MAX = 1000, n = nums.size();

    for (size_t i = 0; i < n; i++)
    {
        if (nums[i] > MAX)
        {
            continue;
        }

        bool positive = (nums[i] > 0);
        int j = i;
        while (true)
        {
            if (nums[j] == id)
            {
                return true;
            }

            if ((positive && nums[j] < 0) || (!positive && nums[j] > 0))
            {
                break;
            }

            if (nums[j] > MAX)
            {
                break;
            }

            int jj = j;
            j = (j + nums[j] % n + n) % n;
            if (jj == j)
            {
                break;
            }

            nums[jj] = id;
        }
        id++;
    }
    return false;
}