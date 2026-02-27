/*
 * 1147. Longest Chunked Palindrome Decomposition
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * Return the largest possible k such that there exists a_1, a_2, ..., a_k such that:
 * 
 * Each a_i is a non-empty string;
 * Their concatenation a_1 + a_2 + ... + a_k is equal to text;
 * For all 1 <= i <= k,  a_i = a_{k+1 - i}.
 * 
 * Example 1:
 * Input: text = "ghiabcdefhelloadamhelloabcdefghi"
 * Output: 7
 * Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
 * 
 * Example 2:
 * Input: text = "merchant"
 * Output: 1
 * Explanation: We can split the string on "(merchant)".
 * 
 * Example 3:
 * Input: text = "antaprezatepzapreanta"
 * Output: 11
 * Explanation: We can split the string on "(a)(nt)(a)(pre)(za)(tpe)(za)(pre)(a)(nt)(a)".
 * 
 * Note:
 * 1 <= text.length <= 1000
 * text consists only of lowercase English characters.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int longestDecomposition(string text) {
        int n = text.size();
        int left = 0, right = n - 1;
        int ans = 0;
        
        while (left <= right) {
            int len = 1;
            bool found = false;
            // 尝试从短到长寻找相等的前后缀
            while (left + len - 1 < right - len + 1) {
                if (text.substr(left, len) == text.substr(right - len + 1, len)) {
                    ans += 2;          // 找到一对
                    left += len;
                    right -= len;
                    found = true;
                    break;
                }
                ++len;
            }
            // 没有找到相等的前后缀，剩下的部分作为一个整体
            if (!found) {
                ++ans;
                break;
            }
        }
        return ans;
    }
};