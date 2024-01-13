/*
Find All Numbers Disappeared in an Array

题目描述
给定一个长度为 n 的数组，其中包含范围为 1 到 n 的整数，有些整数重复了多次，有些整数
没有出现，求 1 到 n 中没有出现过的整数。

题解
利用数组这种数据结构建立 n 个桶，把所有重复出现的位置进行标记，然后再遍历一遍数组，
即可找到没有出现过的数字。进一步地，我们可以直接对原数组进行标记：把重复出现的数字在
原数组出现的位置设为负数，最后仍然为正数的位置即为没有出现过的数。
 */
#include <cmath>
#include <vector>
using namespace std;

vector<int> findDisappearedNumbers(vector<int>& nums) {
    int n = nums.size();

    for (size_t i = 0; i < n; i++) {
        while (nums[i] != i + 1) {
            if (nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            } else {
                break;
            }
        }
    }

    vector<int> res;
    for (size_t i = 0; i < n; i++) {
        if (nums[i] != i + 1) {
            res.push_back(i + 1);
        }
    }

    return res;
}

vector<int> findDisappearedNumbers1(vector<int>& nums) {
    for (const int& num : nums) {
        int pos = abs(num) - 1;
        if (nums[pos] > 0) {
            nums[pos] = -nums[pos];
        }
    }

    vector<int> ans{};
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > 0) {
            ans.push_back(i + 1);
        }
    }
    return ans;
}