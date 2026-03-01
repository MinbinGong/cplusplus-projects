/**
 * 1318. Minimum Flips to Make a OR b Equal to c
 * 
 * Given 3 positives numbers a, b and c. Return the minimum flips required in some bits of a and b to make ( a OR b == c ). (bitwise OR operation).
 * Flip operation consists of change any single bit 1 to 0 or change the bit 0 to 1 in their binary representation.
 * 
 * Example 1:
 * Input: a = 2, b = 6, c = 5
 * Output: 3
 * Explanation: After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)
 * 
 * Example 2:
 * Input: a = 4, b = 2, c = 7
 * Output: 1
 * 
 * Example 3:
 * Input: a = 1, b = 2, c = 3
 * Output: 0
 * 
 * Note:
 * 1 <= a <= 10^9
 * 1 <= b <= 10^9
 * 1 <= c <= 10^9
 */
class Solution {
public:
    int minFlips(int a, int b, int c) {
        int flips = 0;
        // Check each bit position (0 to 30, since numbers up to 10^9 fit in 31 bits)
        for (int i = 0; i < 31; ++i) {
            int ai = (a >> i) & 1;
            int bi = (b >> i) & 1;
            int ci = (c >> i) & 1;
            
            if (ci == 1) {
                // Need (ai | bi) = 1. If both 0, one flip required.
                if ((ai | bi) == 0) flips += 1;
            } else {
                // Need both 0. Flip each 1 to 0.
                flips += ai + bi;
            }
        }
        return flips;
    }
};