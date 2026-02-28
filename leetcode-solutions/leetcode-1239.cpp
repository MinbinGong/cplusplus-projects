/*
 * 1239. Maximum Length of a Concatenated String with Unique Characters
 *
 * Given an array of strings arr. String s is a concatenation of a sub-sequence of arr which have unique characters.
 *
 * Return the maximum possible length of s.
 * 
 * Example 1:
 * 
 * Input: arr = ["un","iq","ue"]
 * Output: 4
 * Explanation: All possible concatenations are "","un","iq","ue","uniq" and "ique".
 * Maximum length is 4.
 * 
 * Example 2:
 * 
 * Input: arr = ["cha","r","act","ers"]
 * Output: 6
 * Explanation: Possible solutions are "chaers" and "acters".
 * 
 * Example 3:
 * 
 * Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
 * Output: 26
 * 
 * Constraints:
 * 
 * 1 <= arr.length <= 16
 * 1 <= arr[i].length <= 26
 * arr[i] contains only lower case English letters.
 */
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int maxLength(vector<string>& arr) {
        int n = arr.size();
        int maxLen = 0;
        
        // 使用DFS/回溯法遍历所有可能的子序列
        function<void(int, int, int)> dfs = [&](int index, int currentMask, int currentLen) {
            // 更新最大长度
            maxLen = max(maxLen, currentLen);
            
            // 从当前位置开始尝试添加字符串
            for (int i = index; i < n; ++i) {
                int mask = 0;
                bool valid = true;
                
                // 检查当前字符串自身是否有重复字符
                for (char c : arr[i]) {
                    int bit = 1 << (c - 'a');
                    if (mask & bit) {  // 当前字符串内部有重复字符
                        valid = false;
                        break;
                    }
                    mask |= bit;
                }
                
                // 如果当前字符串自身有效，并且与已选字符串没有重复字符
                if (valid && (currentMask & mask) == 0) {
                    // 选择当前字符串，继续搜索
                    dfs(i + 1, currentMask | mask, currentLen + arr[i].length());
                }
            }
        };
        
        // 从第0个位置开始搜索
        dfs(0, 0, 0);
        return maxLen;
    }
};

// 方法2：位掩码 + 动态规划（使用集合）
class Solution2 {
public:
    int maxLength(vector<string>& arr) {
        // 预处理：过滤掉有重复字符的字符串，并转换为位掩码
        vector<int> masks;
        for (const string& s : arr) {
            int mask = 0;
            bool valid = true;
            for (char c : s) {
                int bit = 1 << (c - 'a');
                if (mask & bit) {
                    valid = false;
                    break;
                }
                mask |= bit;
            }
            if (valid) {
                masks.push_back(mask);
            }
        }
        
        // 使用集合记录所有可能的组合
        vector<int> dp = {0};
        int maxLen = 0;
        
        for (int mask : masks) {
            int size = dp.size();
            for (int i = 0; i < size; ++i) {
                if ((dp[i] & mask) == 0) {
                    int newMask = dp[i] | mask;
                    dp.push_back(newMask);
                    // 计算长度
                    int len = 0;
                    for (int j = 0; j < 26; ++j) {
                        if (newMask & (1 << j)) len++;
                    }
                    maxLen = max(maxLen, len);
                }
            }
        }
        
        return maxLen;
    }
};

// 方法3：位掩码 + 迭代
class Solution3 {
public:
    int maxLength(vector<string>& arr) {
        // 预处理
        vector<pair<int, int>> validMasks;  // (mask, length)
        for (const string& s : arr) {
            int mask = 0;
            bool valid = true;
            for (char c : s) {
                int bit = 1 << (c - 'a');
                if (mask & bit) {
                    valid = false;
                    break;
                }
                mask |= bit;
            }
            if (valid) {
                validMasks.push_back({mask, (int)s.length()});
            }
        }
        
        int maxLen = 0;
        int m = validMasks.size();
        
        // 遍历所有子集
        for (int subset = 0; subset < (1 << m); ++subset) {
            int currentMask = 0;
            int currentLen = 0;
            bool conflict = false;
            
            for (int i = 0; i < m; ++i) {
                if (subset & (1 << i)) {
                    auto [mask, len] = validMasks[i];
                    if ((currentMask & mask) == 0) {
                        currentMask |= mask;
                        currentLen += len;
                    } else {
                        conflict = true;
                        break;
                    }
                }
            }
            
            if (!conflict) {
                maxLen = max(maxLen, currentLen);
            }
        }
        
        return maxLen;
    }
};

// 方法4：优化版DFS，先对字符串按长度降序排序
class Solution4 {
public:
    int maxLength(vector<string>& arr) {
        int n = arr.size();
        
        // 预处理：将字符串转换为位掩码，并过滤无效字符串
        vector<pair<int, int>> valid;  // (mask, length)
        for (const string& s : arr) {
            int mask = 0;
            bool ok = true;
            for (char c : s) {
                int bit = 1 << (c - 'a');
                if (mask & bit) {
                    ok = false;
                    break;
                }
                mask |= bit;
            }
            if (ok) {
                valid.push_back({mask, (int)s.length()});
            }
        }
        
        // 按字符串长度降序排序
        sort(valid.begin(), valid.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        });
        
        int maxLen = 0;
        
        function<void(int, int, int)> dfs = [&](int index, int mask, int len) {
            if (len > maxLen) {
                maxLen = len;
            }
            
            // 剪枝：如果剩下的字符串即使全选也不可能超过当前最大值，则返回
            int remaining = 0;
            for (int i = index; i < valid.size(); ++i) {
                remaining += valid[i].second;
            }
            if (len + remaining <= maxLen) {
                return;
            }
            
            for (int i = index; i < valid.size(); ++i) {
                if ((mask & valid[i].first) == 0) {
                    dfs(i + 1, mask | valid[i].first, len + valid[i].second);
                }
            }
        };
        
        dfs(0, 0, 0);
        return maxLen;
    }
};

// 测试用例示例：
// 输入: arr = ["un","iq","ue"]
// 输出: 4
// 解释: 可以选择 "un" 和 "ue" 或者 "iq" 和 "ue"
//
// 输入: arr = ["cha","r","act","ers"]
// 输出: 6
// 解释: 可以选择 "cha" 和 "ers" 或者 "act" 和 "ers"
//
// 输入: arr = ["abcdefghijklmnopqrstuvwxyz"]
// 输出: 26
// 解释: 整个字母表中每个字母都只出现一次
//
// 输入: arr = ["aa","bb"]
// 输出: 0
// 解释: 每个字符串自身都有重复字符，无法选择任何字符串

// 复杂度分析：
// 方法1（DFS）：
// - 时间复杂度：O(2^n)，其中n是字符串数量，每个字符串有选或不选两种选择
// - 空间复杂度：O(n)，递归栈深度
//
// 方法2（位掩码+动态规划）：
// - 时间复杂度：O(n * 2^n)，最坏情况下每个字符串都会产生新的组合
// - 空间复杂度：O(2^n)，存储所有可能的组合
//
// 方法3（迭代）：
// - 时间复杂度：O(2^n * n)
// - 空间复杂度：O(1)
//
// 方法4（优化DFS）：
// - 时间复杂度：O(2^n)，但通过剪枝和排序优化，实际运行更快
// - 空间复杂度：O(n)