/*
 * 1071. Greatest Common Divisor of Strings
 * 
 * For strings S and T, we say "T divides S" if and only if S = T + ... + T  (T concatenated with itself 1 or more times)
 * 
 * Return the largest string X such that X divides str1 and X divides str2.
 * 
 * 
 * Example 1:
 * Input: str1 = "ABCABC", str2 = "ABC"
 * Output: "ABC"
 * 
 * Example 2:
 * Input: str1 = "ABABAB", str2 = "ABAB"
 * Output: "AB"
 * 
 * Example 3:
 * Input: str1 = "LEET", str2 = "CODE"
 * Output: ""
 * 
 * Note:
 * 1 <= str1.length <= 1000
 * 1 <= str2.length <= 1000
 * str1[i] and str2[i] are English uppercase letters.
 * 
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        // 如果两个字符串拼接后不相等，则不存在公因子
        if (str1 + str2 != str2 + str1) return "";
        
        // 最大公因子长度就是两字符串长度的最大公约数
        int len = gcd(str1.size(), str2.size());
        return str1.substr(0, len);
    }

private:
    int gcd(int a, int b) {
        while (b) {
            int temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }
};