/*
 * 1056. Confusing Number
 *
 * Given a number N, return true if and only if it is a confusing number, which satisfies the following condition:
 * 
 * We can rotate digits by 180 degrees to form new digits. When 0, 1, 6, 8, 9 are rotated 180 degrees, they become 0, 1, 9, 8, 6 respectively. When 2, 3, 4, 5 and 7 are rotated 180 degrees, they become invalid. A confusing number is a number that when rotated 180 degrees becomes a different number with each digit valid.
 * 
 * Example 1:
 * Input: 6
 * Output: true
 * Explanation: 
 * We get 9 after rotating 6, 9 is a valid number and 9!=6.
 * 
 * Example 2:
 * Input: 89
 * Output: true
 * Explanation: 
 * We get 68 after rotating 89, 86 is a valid number and 86!=89.
 * 
 * Example 3:
 * Input: 11
 * Output: false
 * Explanation: 
 * We get 11 after rotating 11, 11 is a valid number but the value remains the same, thus 11 is not a confusing number.
 * 
 * Note:
 * 1. 1 <= N <= 10^9
 *  
 */
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

class Solution1 {
public:
    bool confusingNumber(int n) {
        // 映射表：下标为原数字，值为旋转180°后的数字，-1表示无效
        vector<int> map = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
        
        int original = n;
        int rotated = 0;
        
        while (n > 0) {
            int digit = n % 10;           // 取出最低位
            
            // 检查当前位是否有效
            if (map[digit] == -1) {
                return false;
            }
            
            // 构建旋转后的数字（注意这里已经在反转数字）
            rotated = rotated * 10 + map[digit];
            n /= 10;
        }
        
        // 如果旋转后与原数相同，返回false
        return rotated != original;
    }
};

class Solution2 {
public:
    bool confusingNumber(int n) {
        string num = to_string(n);
        unordered_map<char, char> map = {
            {'0', '0'},
            {'1', '1'},
            {'6', '9'},
            {'8', '8'},
            {'9', '6'}
        };
        
        string rotated;
        
        // 从原数字的末尾开始构建旋转后的数字（因为旋转是整体翻转）
        for (int i = num.length() - 1; i >= 0; i--) {
            char ch = num[i];
            
            // 检查是否有无效数字
            if (map.find(ch) == map.end()) {
                return false;
            }
            
            rotated += map[ch];
        }
        
        // 处理前导零：stoi会自动去掉前导零
        return stoi(rotated) != n;
    }
};

class Solution3 {
public:
    bool confusingNumber(int n) {
        vector<int> original;
        vector<int> rotated;
        int temp = n;
        
        while (temp > 0) {
            int digit = temp % 10;
            
            // 检查有效性
            if (!(digit == 0 || digit == 1 || digit == 6 || digit == 8 || digit == 9)) {
                return false;
            }
            
            original.push_back(digit);
            
            // 记录旋转后的数字
            if (digit == 6) rotated.push_back(9);
            else if (digit == 9) rotated.push_back(6);
            else rotated.push_back(digit);
            
            temp /= 10;
        }
        
        // 因为取数字是从低位到高位，需要反转才能比较
        reverse(original.begin(), original.end());
        return original != rotated;
    }
};