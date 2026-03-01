/**
 * 1299. Replace Elements with Greatest Element on Right Side
 * 
 * Given an array arr, replace every element in that array with the greatest element among the elements to its right, and replace the last element with -1.
 * 
 * After doing so, return the array.
 * 
 * Example 1:
 * Input: arr = [17,18,5,4,6,1]
 * Output: [18,6,6,6,1,-1]
 * 
 * Example 2:
 * Input: arr = [400]
 * Output: [-1]
 * 
 * Note:
 * 1 <= arr.length <= 10^4
 * 1 <= arr[i] <= 10^5
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n = arr.size();
        int maxRight = -1;  // 记录右边最大值，最后一个元素右边无元素，所以初始为 -1
        for (int i = n - 1; i >= 0; --i) {
            int cur = arr[i];       // 保存当前值
            arr[i] = maxRight;       // 替换为右边最大值
            maxRight = max(maxRight, cur); // 更新右边最大值（包含当前值）
        }
        return arr;
    }
};