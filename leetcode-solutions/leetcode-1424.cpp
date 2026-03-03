/**
 * 1424. Diagonal Traverse II
 * 
 * Given a list of lists of integers, nums, return all elements of nums in diagonal order as shown in the below images.
 * 
 * Example 1:
 * 
 * Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [1,4,2,7,5,3,8,6,9]
 * 
 * Example 2:
 * 
 * Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
 * Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
 * 
 * Example 3:
 * 
 * Input: nums = [[1,2,3],[4],[5,6,7],[8],[9,10,11]]
 * Output: [1,4,2,5,3,8,6,9,7,10,11]
 * 
 * Example 4:
 * 
 * Input: nums = [[1,2,3,4,5,6]]
 * Output: [1,2,3,4,5,6]
 * 
 * Note:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i].length <= 10^5
 * 1 <= nums[i][j] <= 10^9
 * There at most 10^5 elements in nums.
 * 
 */
#include <vector>
#include <map>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        // map from diagonal index (i+j) to list of elements
        map<int, vector<int>> diagMap;
        
        // traverse rows in increasing order
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums[i].size(); ++j) {
                diagMap[i + j].push_back(nums[i][j]);
            }
        }
        
        vector<int> result;
        // process diagonals in increasing order of index
        for (auto& [d, vec] : diagMap) {
            // current order is increasing row; we need decreasing row
            reverse(vec.begin(), vec.end());
            for (int val : vec) {
                result.push_back(val);
            }
        }
        return result;
    }
};