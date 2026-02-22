/*
 * Next Greater Element III
 *
 * Given a positive 32-bit integer n, you need to find the smallest 32-bit integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive 32-bit integer exists, you need to return -1.
 * 
 * Note:
 * The given n is a positive 32-bit integer.
 * 
 * Example:
 * Input: 12
 * Output: 21
 * 
 * Input: 21
 * Output: -1
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int nextGreaterElement(int n) {
        string s = to_string(n);
        // 1. 从右向左找第一个下降的位置
        int i = s.size() - 2;
        while (i >= 0 && s[i] >= s[i + 1]) {
            i--;
        }
        if (i < 0) return -1; // 已经是最大排列

        // 2. 从右向左找第一个大于 s[i] 的位置
        int j = s.size() - 1;
        while (j >= 0 && s[j] <= s[i]) {
            j--;
        }
        swap(s[i], s[j]);

        // 3. 反转 i+1 到末尾
        reverse(s.begin() + i + 1, s.end());

        // 4. 转换为整数并检查溢出
        long long res = stoll(s);
        if (res > INT_MAX) return -1;
        return res;
    }
};