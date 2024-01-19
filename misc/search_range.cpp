#include <iostream>
#include <vector>
using namespace std;

int lower_bound(vector<int>& nums, int target) {
    int l = 0, r = nums.size(), mid;
    while (l < r) {
        mid = l + (r - l) / 2;
        if (nums[mid] >= target) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int upper_bound(vector<int>& nums, int target) {
    int l = 0, r = nums.size(), mid;
    while (l < r) {
        mid = l + (r - l) / 2;
        if (nums[mid] > target) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

vector<int> search_range(vector<int>& nums, int target) {
    if (nums.empty()) {
        return vector<int>{-1, -1};
    }

    int lower = lower_bound(nums, target);
    int upper = upper_bound(nums, target);
    if (lower == int(nums.size()) || nums[lower] != target) {
        return vector<int>{-1, -1};
    }
    return vector<int>{lower, upper - 1};
}

int main()
{
    vector<int> src{3, 6, 6, 8, 8, 8, 8, 10, 11, 12};
    vector<int> res = search_range(src, 8);

    for (const auto &num : res) {
        cout << num << endl;
    }

    return 0;
}
