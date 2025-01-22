/*
 * leetcode-697
 * Degree of an Array
 * 
 * Given a non-empty array of non-negative integers nums, 
 * the degree of this array is defined as the maximum frequency of any one of its elements.
 * 
 * Your task is to find the smallest possible length of a (contiguous) subarray of nums,
 * that has the same degree as nums.
 */
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> hash;
        int maxCount = 0, same = 1, sameY = 1;
        for (int i = 0; i < nums.size(); ++i) {
            same = 1, sameY = 1;
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[i][1] == nums[j][1]) {
                    ++sameY;
                    if (nums[i][0] == nums[j][0]) {
                        ++same;
                    }
                } else {
                    double dx = points[i][0] - points[j][0], dy = points[i][1] - points[j][1];
                    ++hash[dx / dy];
                }
            }
            maxCount = max(maxCount, sameY);
            for (auto item : hash) {
                maxCount = max(maxCount, same + item.second);
            }
            hash.clear();
        }
        return maxCount;
    }
};