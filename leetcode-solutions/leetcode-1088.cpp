/*
 * 1088. Confusing Number II
 *
 * We can rotate digits by 180 degrees to form new digits. When 0, 1, 6, 8, 9 are rotated 180 degrees, they become 0, 1, 9, 8, 6 respectively. When 2, 3, 4, 5 and 7 are rotated 180 degrees, they become invalid.
 * A confusing number is a number that when rotated 180 degrees becomes a different number with each digit valid.(Note that the rotated number can be greater than the original number.)
 * Given a positive integer N, return the number of confusing numbers between 1 and N inclusive.
 * 
 * Example 1:
 * Input: 20
 * Output: 6
 * Explanation: 
 * The confusing numbers are [6,9,10,16,18,19].
 * 6 converts to 9.
 * 9 converts to 6.
 * 10 converts to 01 which is just 1.
 * 16 converts to 91.
 * 18 converts to 81.
 * 19 converts to 61.
 * 
 * Example 2:
 * Input: 100
 * Output: 19
 * Explanation: 
 * The confusing numbers are [6,9,10,16,18,19,60,61,66,68,80,81,86,89,90,91,98,99,100].
 * 
 * Note:
 * 1 <= N <= 10^9
 * 
 */
#include <vector>
#include <string>
#include <functional>
using namespace std;

class Solution {
public:
    int confusingNumberII(int n) {
        // 数字映射表：0→0, 1→1, 6→9, 8→8, 9→6，其他为-1表示无效
        vector<int> mapping = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
        
        // 将n转换为字符串，用于DFS中的上限判断
        string limit = to_string(n);
        
        // 检查一个数字是否为混淆数字
        auto isConfusing = [&](long long num) -> bool {
            long long rotated = 0;
            long long temp = num;
            
            while (temp > 0) {
                int digit = temp % 10;
                // 如果数字无效，直接返回false（但DFS生成的数字都是有效的）
                if (mapping[digit] == -1) return false;
                rotated = rotated * 10 + mapping[digit];
                temp /= 10;
            }
            return rotated != num;
        };
        
        // DFS递归函数
        function<int(int, bool, long long)> dfs = [&](int pos, bool isLimit, long long current) -> int {
            // 递归终止条件：处理完所有位数
            if (pos >= limit.size()) {
                // 当前数字为0或大于n时不计入
                if (current == 0 || current > n) return 0;
                // 检查是否为混淆数字
                return isConfusing(current) ? 1 : 0;
            }
            
            int count = 0;
            int maxDigit = isLimit ? (limit[pos] - '0') : 9;
            
            // 尝试所有可能的数字
            for (int digit = 0; digit <= maxDigit; digit++) {
                // 跳过无效数字
                if (mapping[digit] == -1) continue;
                
                // 递归调用
                bool nextLimit = isLimit && (digit == maxDigit);
                long long nextCurrent = current * 10 + digit;
                
                // 如果当前数字为0，继续递归（避免前导零）
                if (current == 0 && digit == 0) {
                    count += dfs(pos + 1, nextLimit, 0);
                } else {
                    count += dfs(pos + 1, nextLimit, nextCurrent);
                }
            }
            
            return count;
        };
        
        return dfs(0, true, 0);
    }
};