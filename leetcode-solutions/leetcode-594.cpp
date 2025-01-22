/*
 * leetcode-594
 * 最长和谐子序列  Longest Harmonious Subsequence
 * 
 * We define a harmonious array as an array
 * where the difference between its maximum value and its minimum value is exactly 1.
 * 
 * Given an integer array nums, return the length of its longest harmonious subsequence
 * among all its possible subsequences.
 */
#include <unordered_map>
#include <vector>
using namespace std;
int findLHS(vector<int>& nums) {
    unordered_map<int, int> hashmap;
    int maxCount = 0;
    for (int i : nums) {
        ++hashmap[i];
        maxCount = max(maxCount, max(hashmap[i] + hashmap[i - 1], hashmap[i] + hashmap[i + 1]));
    }
    return maxCount;
}