/*
 * Minimum Factorization
 * 
 * Given a positive integer num, return the smallest positive integer x whose multiplication of each digit equals num.
 * If there is no answer or the answer is not fit in 32-bit signed integer, return 0.
 * 
 * Example 1:
 * Input: num = 48
 * Output: 68
 * 
 * Example 2:
 * Input: num = 15
 * Output: 35
 * 
 * Constraints:
 * 1 <= num <= 231 - 1
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int smallestFactorization(int num) {
        // 处理个位数的情况
        if (num < 10) {
            return num;
        }

        vector<int> digits;
        int temp = num;
        // 从9到2依次尝试分解
        for (int d = 9; d >= 2; --d) {
            while (temp % d == 0) {
                digits.push_back(d);
                temp /= d;
            }
        }

        // 如果最后temp没被除成1，说明存在大于7的质因子，无法分解
        if (temp != 1) {
            return -1;
        }

        // 将因子升序排序，以获得最小的数字
        sort(digits.begin(), digits.end());

        long long result = 0;
        for (int d : digits) {
            result = result * 10 + d;
            // 检查是否溢出32位有符号整数
            if (result > INT_MAX) {
                return 0;
            }
        }

        return (int)result;
    }
};