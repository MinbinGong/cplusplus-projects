/*
 * Super Palindromes
 *
 * Given a positive integer N, return the number of positive integers less than or equal to N that are superpalindromes.
 * 
 * A superpalindrome is a palindrome whose square is also a palindrome.
 * 
 * Example 1:
 * Input: 1000
 * Output: 4
 * Explanation: 4 superpalindromes are 1, 4, 9, 121.
 * 
 * Note:
 * 1 <= N <= 10^18.
 */
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int superpalindromesInRange(string left, string right) {
        long long L = stoll(left);
        long long R = stoll(right);
        int MAGIC = 100000; // 10^5, 用于生成回文根的上限
        int ans = 0;

        // 1. 构造奇数长度的回文根 (例如: 123 -> 12321)
        for (int k = 1; k <= MAGIC; ++k) {
            string s = to_string(k);
            // 奇数长度拼接：s + s[-2::-1]
            string revPart = s.substr(0, s.length() - 1);
            reverse(revPart.begin(), revPart.end());
            string p = s + revPart;

            long long root = stoll(p);
            long long square = root * root;
            if (square > R) break; // 超过上限，提前终止
            if (square >= L && isPalindrome(square)) {
                ans++;
            }
        }

        // 2. 构造偶数长度的回文根 (例如: 123 -> 123321)
        for (int k = 1; k <= MAGIC; ++k) {
            string s = to_string(k);
            // 偶数长度拼接：s + reverse(s)
            string rev = s;
            reverse(rev.begin(), rev.end());
            string p = s + rev;

            long long root = stoll(p);
            long long square = root * root;
            if (square > R) break; // 超过上限，提前终止
            if (square >= L && isPalindrome(square)) {
                ans++;
            }
        }

        return ans;
    }

private:
    // 辅助函数：判断一个数是否为回文数
    bool isPalindrome(long long x) {
        if (x < 0) return false;
        string s = to_string(x);
        int i = 0, j = s.length() - 1;
        while (i < j) {
            if (s[i++] != s[j--]) return false;
        }
        return true;
    }
};