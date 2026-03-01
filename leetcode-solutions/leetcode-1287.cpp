/**
 * 1287. Element Appearing More Than 25% In Sorted Array
 * 
 * Given an integer array sorted in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time.
 * 
 * Return that integer.
 * 
 * Example 1:
 * Input: arr = [1,2,2,6,6,6,6,7,10]
 * Output: 6
 * 
 * Note:
 * 1 <= arr.length <= 10^4
 * 0 <= arr[i] <= 10^5
 */
#include <vector>
using namespace std;

class Solution1 {
public:
    int findSpecialInteger(vector<int>& arr) {
        int n = arr.size();
        int span = n / 4; // 计算25%长度的步长
        
        // 遍历检查每个元素与其后第span个元素是否相等
        for (int i = 0; i < n - span; ++i) {
            if (arr[i] == arr[i + span]) {
                return arr[i];
            }
        }
        
        return -1; // 根据题目描述，实际上不会执行到这里
    }
};

class Solution2 {
public:
    int findSpecialInteger(vector<int>& arr) {
        int n = arr.size();
        int target = n / 4;
        int count = 1;
        int currentNum = arr[0];
        
        for (int i = 1; i < n; ++i) {
            if (arr[i] == currentNum) {
                count++;
                if (count > target) {
                    return currentNum;
                }
            } else {
                currentNum = arr[i];
                count = 1;
            }
        }
        
        return currentNum; // 当数组长度为1时，直接返回第一个元素
    }
};