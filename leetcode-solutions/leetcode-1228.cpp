/**
 * 1228. Missing Number In Arithmetic Progression
 *
 * In some array arr, the values were in arithmetic progression: the values arr[i+1] - arr[i] are all equal for every 0 <= i < arr.length - 1.
 *
 * A value from arr was removed that was not the first or last value in the array.
 *
 * Given arr, return the removed value.
 *
 *
 *
 * Example 1:
 *
 * Input: arr = [5,7,11,13]
 * Output: 9
 * Explanation: The previous array was [5,7,9,11,13].
 *
 * Example 2:
 *
 * Input: arr = [15,13,12]
 * Output: 14
 * Explanation: The previous array was [15,14,13,12].
 *
 *
 * Constraints:
 *
 * 3 <= arr.length <= 1000
 * 0 <= arr[i] <= 10^5
 * The given array is guaranteed to be valid.
 * 
 */
#include <vector>

using namespace std;

class Solution1 {
public:
    int missingNumber(vector<int>& arr) {
        int n = arr.size();
        
        // 计算等差数列的公差
        // 注意：使用浮点数除法避免整数除法精度问题
        double d = (double)(arr.back() - arr.front()) / n;
        
        // 二分查找缺失的位置
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            // 计算mid位置的理论值
            double expected = arr[0] + mid * d;
            
            if (abs(arr[mid] - expected) < 1e-9) {
                // 如果arr[mid]等于理论值，说明缺失位置在右侧
                left = mid + 1;
            } else {
                // 否则缺失位置在左侧（包括mid）
                right = mid;
            }
        }
        
        // 计算缺失的值
        return arr[0] + left * d;
    }
};

// 方法2：线性扫描解法
class Solution2 {
public:
    int missingNumber(vector<int>& arr) {
        int n = arr.size();
        
        // 计算公差
        int totalDiff = arr.back() - arr.front();
        int d = totalDiff / n;  // 整数除法，公差为整数
        
        // 遍历数组找到缺失的位置
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i + 1] - arr[i] != d) {
                return arr[i] + d;
            }
        }
        
        // 理论上不会执行到这里
        return arr[0];
    }
};

// 方法3：使用相邻差值确定公差
class Solution3 {
public:
    int missingNumber(vector<int>& arr) {
        int n = arr.size();
        
        // 计算公差，取最常见的差值
        int d1 = arr[1] - arr[0];
        int d2 = arr[2] - arr[1];
        
        // 确定正确的公差
        int d = (abs(d1) < abs(d2)) ? d1 : d2;
        
        // 查找缺失的位置
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i + 1] - arr[i] != d) {
                return arr[i] + d;
            }
        }
        
        return arr[0];
    }
};

// 方法4：数学公式直接计算
class Solution4 {
public:
    int missingNumber(vector<int>& arr) {
        int n = arr.size();
        // 等差数列求和公式：S = n/2 * (首项 + 末项)
        // 缺失的数 = 完整数列的和 - 当前数列的和
        int first = arr.front();
        int last = arr.back();
        
        // 完整数列的和
        int fullSum = (first + last) * (n + 1) / 2;
        
        // 当前数列的和
        int currentSum = 0;
        for (int num : arr) {
            currentSum += num;
        }
        
        return fullSum - currentSum;
    }
};

// 测试用例示例：
// 输入: [5,7,11,13] -> 输出: 9
// 输入: [15,13,12] -> 输出: 14