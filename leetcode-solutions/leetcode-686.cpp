/*
 * Repeated String Match
 *
 * Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.
 * 
 * For example, with A = "abcd" and B = "cdabcdab".
 * 
 * Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").
 * 
 * Note:
 *
 * The length of A and B will be between 1 and 10000.
 * 
 * Example 1:
 *
 * Input: A = "abcd", B = "cdabcdab"
 * Output: 3
 * 
 * Example 2:
 *
 * Input: A = "a", B = "aa"
 * Output: 2
 * 
 * Example 3:
 *
 * Input: A = "a", B = "a"
 * Output: 1
 * 
 * Example 4:
 *
 * Input: A = "abc", B = "wxyz"
 * Output: -1
 * 
 * Note:
 *
 * The length of A and B will be between 1 and 10000.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        int n = A.size(), m = B.size();
        string s = A;
        int cnt = 1;
        // 重复A直到长度至少为B
        while (s.size() < m) {
            s += A;
            cnt++;
        }
        // 检查当前是否包含B
        if (s.find(B) != string::npos) return cnt;
        // 再多加一次试试（处理边界情况）
        s += A;
        cnt++;
        if (s.find(B) != string::npos) return cnt;
        return -1;
    }
};