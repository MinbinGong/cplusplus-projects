/*
 * 1100. Find K-Length Substrings With No Repeated Characters
 * 
 * Given a string S, return the number of substrings of length K with no repeated characters.
 * 
 * 1 <= S.length <= 10^4
 * All characters of S are lowercase English letters.
 * 1 <= K <= 10^4
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int numKLenSubstrNoRepeats(string s, int k) {
        int n = s.size();
        // 边界条件：如果k大于字符串长度或大于26（字母种类数），直接返回0
        if (k > n || k > 26) return 0;
        
        int cnt[128] = {0};  // 字符计数数组
        int ans = 0;
        int left = 0;
        
        for (int right = 0; right < n; right++) {
            // 添加右边界字符
            cnt[s[right]]++;
            
            // 如果窗口中有重复字符或窗口大小超过k，移动左边界
            while (cnt[s[right]] > 1 || right - left + 1 > k) {
                cnt[s[left]]--;
                left++;
            }
            
            // 如果窗口大小恰好为k，找到一个有效子串
            if (right - left + 1 == k) {
                ans++;
            }
        }
        
        return ans;
    }
};