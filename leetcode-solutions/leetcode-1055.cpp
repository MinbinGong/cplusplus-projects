/*
 * 1055. Shortest Way to Form String
 *
 * From any string, we can form a subsequence of that string by deleting some number of characters (possibly no deletions).
 * 
 * Given two strings source and target, return the minimum number of subsequences of source such that their concatenation equals target.  If the task is impossible, return -1.
 * 
 * Example 1:
 * Input: source = "abc", target = "abcbc"
 * Output: 2
 * Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".
 * 
 * Example 2:
 * Input: source = "abc", target = "acdbc"
 * Output: -1
 * Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.
 * 
 * Example 3:
 * Input: source = "xyz", target = "xzyxz"
 * Output: 3
 * Explanation: The target string can be constructed as follows "xz" + "y" + "xz".
 * 
 * Note:
 * 1. 1 <= source.length <= 1000
 * 2. 1 <= target.length <= 10000
 * 3. source and target contain only lowercase English letters.
 * 
 */
#include <string>
#include <unordered_set>
using namespace std;

class Solution1 {
public:
    int shortestWay(string source, string target) {
        int i = 0;          // source 指针
        int j = 0;          // target 指针
        int count = 0;      // 使用的子序列数量
        int n = source.size();
        int m = target.size();
        
        while (j < m) {
            int prevJ = j;          // 记录本轮开始时的位置
            i = 0;                  // 每次从source开头重新匹配
            
            // 遍历source，尽可能匹配target
            while (i < n && j < m) {
                if (source[i] == target[j]) {
                    j++;            // 匹配成功，移动target指针
                }
                i++;                // 无论是否匹配，source指针都要移动
            }
            
            // 如果本轮没有匹配到任何新字符，说明无法匹配
            if (j == prevJ) {
                return -1;
            }
            
            count++;                // 使用了一个子序列
        }
        
        return count;
    }
};

class Solution2 {
public:
    int shortestWay(string source, string target) {
        // 预处理：记录每个字符在source中的所有出现位置
        vector<int> pos[26];
        for (int i = 0; i < source.size(); i++) {
            pos[source[i] - 'a'].push_back(i);
        }
        
        // 检查target中是否有source不存在的字符
        for (char c : target) {
            if (pos[c - 'a'].empty()) {
                return -1;
            }
        }
        
        int res = 1;
        int lastPos = -1;  // 上一个匹配到的位置
        
        for (char c : target) {
            int idx = c - 'a';
            // 在pos[idx]中二分查找第一个大于lastPos的位置
            auto it = upper_bound(pos[idx].begin(), pos[idx].end(), lastPos);
            
            if (it == pos[idx].end()) {
                // 找不到更大的位置，需要开始一个新的子序列
                res++;
                lastPos = pos[idx][0];  // 使用该字符的第一个出现位置
            } else {
                lastPos = *it;
            }
        }
        
        return res;
    }
};

class Solution3 {
public:
    int shortestWay(string source, string target) {
        int res = 1;
        int pos = -1;
        
        for (char c : target) {
            // 检查字符是否存在
            if (source.find(c) == string::npos) {
                return -1;
            }
            
            // 从 pos+1 位置开始找 c
            pos = source.find(c, pos + 1);
            
            if (pos == string::npos) {
                // 在当前子序列中找不到，开始新子序列
                res++;
                pos = source.find(c);
            }
        }
        
        return res;
    }
};