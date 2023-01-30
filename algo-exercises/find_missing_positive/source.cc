#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int find_missing_positive(vector<int> &nums)
{
    unordered_set<int> my_set;
    int max_num = 0;

    for (auto const item : nums)
    {
        my_set.insert(item);
        if (max_num < item)
        {
            max_num = item;
        }
    }

    int i = 1;
    while (i <= max_num)
    {
        if (my_set.find(i) == my_set.end())
        {
            return i;
        }
        ++i;
    }

    return i;
}

int main()
{
    vector<int> src{7, 8, 9, 11, 12};

    int ret = find_missing_positive(src);

    cout << ret << endl;

    return 0;
}