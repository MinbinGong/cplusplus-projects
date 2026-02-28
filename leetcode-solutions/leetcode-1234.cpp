/*
 * 1234. Replace the Substring for Balanced String
 *
 * You are given a string containing only 4 kinds of characters 'Q', 'W', 'E' and 'R'.
 *
 * A string is said to be balanced if each of its characters appears n/4 times where n is the length of the string.
 *
 * Return the minimum length of the substring that can be replaced with any other string of the same length to make the original string s balanced.
 *
 * Return 0 if the string is already balanced.
 *
 * Example 1:
 * 
 * Input: s = "QWER"
 * Output: 0
 * Explanation: s is already balanced.
 * 
 * Example 2:
 * 
 * Input: s = "QQWE"
 * Output: 1
 * Explanation: We need to replace a 'Q' to 'R', so that "RQWE" (or "QRWE") is balanced.
 * 
 * Example 3:
 * 
 * Input: s = "QQQW"
 * Output: 2
 * Explanation: We can replace the substring "QQ" with "ER".
 * 
 * Example 4:
 * 
 * Input: s = "QQQQ"
 * Output: 3
 * Explanation: We can replace the last 3 'Q' to make s = "QWER".
 * 
 * Note:
 * 1 <= s.length <= 10^5
 * s.length is a multiple of 4
 * s contains only 'Q', 'W', 'E' and 'R'.
 * 
 */
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution1 {
public:
    int balancedString(string s) {
        int n = s.length();
        int target = n / 4;  // 每个字符应该出现的次数
        
        // 统计每个字符的出现次数
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        
        // 如果已经平衡，直接返回0
        if (count['Q'] == target && count['W'] == target && 
            count['E'] == target && count['R'] == target) {
            return 0;
        }
        
        int left = 0;
        int minLen = INT_MAX;
        
        // 滑动窗口：寻找一个子串，使得子串外的字符都不超过target
        for (int right = 0; right < n; ++right) {
            // 将右指针指向的字符从窗口外移到窗口内
            count[s[right]]--;
            
            // 当窗口外的所有字符都不超过target时，尝试收缩窗口
            while (left <= right && 
                   count['Q'] <= target && 
                   count['W'] <= target && 
                   count['E'] <= target && 
                   count['R'] <= target) {
                // 更新最小长度
                minLen = min(minLen, right - left + 1);
                
                // 将左指针指向的字符从窗口内移回窗口外
                count[s[left]]++;
                left++;
            }
        }
        
        return minLen;
    }
};

// 方法2：更直观的滑动窗口解法
class Solution2 {
public:
    int balancedString(string s) {
        int n = s.length();
        int target = n / 4;
        
        // 统计每个字符的总数
        unordered_map<char, int> total;
        for (char c : s) {
            total[c]++;
        }
        
        // 计算需要替换的字符数量
        unordered_map<char, int> need;
        for (char c : {'Q', 'W', 'E', 'R'}) {
            if (total[c] > target) {
                need[c] = total[c] - target;
            }
        }
        
        // 如果不需要替换任何字符
        if (need.empty()) {
            return 0;
        }
        
        int left = 0;
        int minLen = INT_MAX;
        unordered_map<char, int> window;
        
        // 滑动窗口：寻找包含所有需要替换字符的最短子串
        for (int right = 0; right < n; ++right) {
            window[s[right]]++;
            
            // 检查当前窗口是否包含了所有需要替换的字符
            while (isValid(window, need)) {
                minLen = min(minLen, right - left + 1);
                window[s[left]]--;
                left++;
            }
        }
        
        return minLen;
    }
    
private:
    bool isValid(unordered_map<char, int>& window, unordered_map<char, int>& need) {
        for (auto& [ch, cnt] : need) {
            if (window[ch] < cnt) {
                return false;
            }
        }
        return true;
    }
};

// 方法3：使用数组代替哈希表（更高效）
class Solution3 {
public:
    int balancedString(string s) {
        int n = s.length();
        int target = n / 4;
        
        // 使用数组统计字符出现次数
        int count[26] = {0};
        for (char c : s) {
            count[c - 'A']++;
        }
        
        int left = 0;
        int minLen = n;
        
        // 滑动窗口
        for (int right = 0; right < n; ++right) {
            count[s[right] - 'A']--;
            
            // 检查窗口外的字符是否都满足条件
            while (left <= right && 
                   count['Q' - 'A'] <= target && 
                   count['W' - 'A'] <= target && 
                   count['E' - 'A'] <= target && 
                   count['R' - 'A'] <= target) {
                minLen = min(minLen, right - left + 1);
                count[s[left] - 'A']++;
                left++;
            }
        }
        
        return minLen;
    }
};

// 测试用例示例：
// 输入: s = "QWER"
// 输出: 0
// 解释: 字符串已经是平衡的
//
// 输入: s = "QQWE"
// 输出: 1
// 解释: 将"W"替换为"R"，得到"QQRE"，然后"Q"和"R"各出现2次
//
// 输入: s = "QQQW"
// 输出: 2
// 解释: 替换前两个"Q"中的一个为"E"，后一个为"R"，得到"QEQR"
//
// 输入: s = "QQQQ"
// 输出: 3
// 解释: 替换任意3个字符，使得每个字符出现1次

// 复杂度分析：
// 时间复杂度：O(n)，其中n是字符串长度，每个字符最多被访问两次（左指针和右指针各一次）
// 空间复杂度：O(1)，只使用了固定大小的数组或哈希表
