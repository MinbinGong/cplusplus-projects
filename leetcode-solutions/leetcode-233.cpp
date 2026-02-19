/*
 * Number of Digit One
 * 
 * Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
 * 
 * Constraints:
 * 1. 0 <= n <= 109
 */
class Solution {
public:
    int countDigitOne(int n) {
        if (n <= 0) return 0;
        
        long long count = 0;
        long long factor = 1; // 10^k, start with units place
        
        while (factor <= n) {
            long long higher = n / (factor * 10);
            int cur = (n / factor) % 10;
            long long lower = n % factor;
            
            if (cur == 0) {
                count += higher * factor;
            } else if (cur == 1) {
                count += higher * factor + lower + 1;
            } else { // cur >= 2
                count += (higher + 1) * factor;
            }
            
            factor *= 10; // move to next digit
        }
        
        return (int)count;
    }
};
