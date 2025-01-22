/*
 * leetcode-217
 * Contains Duplicate
 * Given an integer array nums, return true if any value appears at least twice in the array,
 * and return false if every element is distinct.
 */
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> hashset;
        for (int i : nums) {
            if (hashset.count(i)) {
                return true;
            }
            hashset.insert(i);
        }
        return false;
    }
};