/**
 * 1134. Armstrong Number
 * Easy
 * 
 * (This problem is an interactive problem.)
 * 
 * Given an integer n, return true if and only if it is an Armstrong number.
 * 
 * The k-digit number n is an Armstrong number if and only if the kth power of each digit sums to n.
 * 
 * Example 1:
 * Input: n = 153
 * Output: true
 * Explanation: 
 * 153 is a 3-digit number, and 153 = 1^3 + 5^3 + 3^3.
 * 
 * Example 2:
 * Input: n = 123
 * Output: false
 * Explanation: 
 * 123 is a 3-digit number, and 123 != 1^3 + 2^3 + 3^3 = 36.
 * 
 * Note:
 * 1 <= n <= 10^8
 * 
 */
class Solution {
public:
    bool isArmstrong(int N) {
        int original = N;
        // 计算位数
        int k = 0;
        int temp = N;
        while (temp) {
            ++k;
            temp /= 10;
        }
        // 处理 N = 0 的情况（0 是阿姆斯特朗数）
        if (k == 0) k = 1;  // 或者不处理，因为后面循环不会执行，sum=0，但为了严谨，可以设置k=1
        
        temp = N;
        int sum = 0;
        while (temp) {
            int digit = temp % 10;
            int power = 1;
            for (int i = 0; i < k; ++i) {
                power *= digit;
            }
            sum += power;
            temp /= 10;
        }
        return sum == original;
    }
};