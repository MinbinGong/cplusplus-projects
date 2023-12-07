// 2Sum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> num_map;
    for (unsigned int i = 0; i < nums.size(); i++) {
        auto complement = num_map.find(target - nums[i]);
        if (complement != num_map.end() && complement->second > i) {
            return {i, complement->second};
        }
        num_map[nums[i]] = i;
    }

    return {-1, -1};
}

vector<int> twoSum2(vector<int>& nums, int target) {
    unsigned int left{0}, right{nums.size() - 1};
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum < target) {
            ++left;
        } else if (sum > target) {
            --right;
        } else {
            return {left + 1, right + 1};
        }
    }
    return {-1, -1};
}

int main() { return 0; }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files
//   to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
