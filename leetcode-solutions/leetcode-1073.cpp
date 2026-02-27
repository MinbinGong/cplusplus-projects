/*
 * 1073. Adding Two Negabinary Numbers
 *
 * Given two numbers arr1 and arr2 in base -2, return the result of adding them together.
 * Each number is given in array format:  as an array of 0s and 1s, from most significant bit to least significant bit.  For example, arr = [1,1,0,1] represents the number (-2)^3 + (-2)^2 + (-2)^0 = -3.  A number arr in array format is also guaranteed to have no leading zeros: either arr == [0] or arr[0] == 1.
 * Return the result of adding arr1 and arr2 in the same format: as an array of 0s and 1s with no leading zeros.
 * 
 * Example 1:
 * Input: arr1 = [1,1,1,1,1], arr2 = [1,0,1]
 * Output: [1,0,0,0,0]
 * Explanation: arr1 represents 11, arr2 represents 5, the output represents 16.
 * 
 * Example 2:
 * Input: arr1 = [0], arr2 = [0]
 * Output: [0]
 * 
 * Example 3:
 * Input: arr1 = [0], arr2 = [1]
 * Output: [1]
 * 
 * Note:
 * 1 <= arr1.length <= 1000
 * 1 <= arr2.length <= 1000
 * arr1 and arr2 have no leading zeros
 * arr1[i] is 0 or 1
 * arr2[i] is 0 or 1
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        vector<int> result;
        int i = arr1.size() - 1, j = arr2.size() - 1;
        int carry = 0;
        
        // 从最低位开始相加
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += arr1[i--];
            if (j >= 0) sum += arr2[j--];
            
            // 当前位：确保结果为 0 或 1
            int bit = sum & 1;  // 等价于 (sum % 2 + 2) % 2
            // 计算下一轮进位
            carry = (bit - sum) / 2;
            
            result.push_back(bit);
        }
        
        // 去除前导零（保留至少一位）
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};