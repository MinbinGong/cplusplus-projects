/*
 * 360. Sort Transformed Array
 *
 * Given a sorted integer array nums and three integers a, b and c, apply a quadratic function of the form f(x) = ax2 + bx + c to each element nums[i] in the array, and return the array in a sorted order.
 * 
 * Example 1:
 * Input: nums = [-4,-2,2,4], a = 1, b = 3, c = 5
 * Output: [3,9,15,33]
 * 
 * Example 2:
 * Input: nums = [-4,-2,2,4], a = -1, b = 3, c = 5
 * Output: [-23,-5,1,7]
 * 
 * Constraints:
 * 1. 1 <= nums.length <= 200
 * 2. -100 <= nums[i], a, b, c <= 100
 * 3. nums is sorted in ascending order.
 * 4. -100 <= a <= 100
 * 5. a != 0
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        int n = nums.size();
        vector<int> result(n);
        int left = 0, right = n - 1;
        // 根据抛物线开口方向决定填充方向
        int idx = (a >= 0) ? n - 1 : 0;
        
        while (left <= right) {
            int valLeft = compute(nums[left], a, b, c);
            int valRight = compute(nums[right], a, b, c);
            
            if (a >= 0) { // 开口向上，两端值大，从后往前填充较大的
                if (valLeft > valRight) {
                    result[idx--] = valLeft;
                    left++;
                } else {
                    result[idx--] = valRight;
                    right--;
                }
            } else { // 开口向下，两端值小，从前往后填充较小的
                if (valLeft < valRight) {
                    result[idx++] = valLeft;
                    left++;
                } else {
                    result[idx++] = valRight;
                    right--;
                }
            }
        }
        return result;
    }

private:
    int compute(int x, int a, int b, int c) {
        return a * x * x + b * x + c;
    }
};