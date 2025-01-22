/*
 * leetcode-268.cpp
 * Missing Number
 * 
 * Given an array nums containing n distinct numbers in the range [0, n],
 * return the only number in the range that is missing from the array.
 */
#include <vector>
#include <numeric>

using namespace std;
int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int sum = n * (n + 1) / 2;
    for (int num : nums) {
        sum -= num;
    }
    return sum;
}