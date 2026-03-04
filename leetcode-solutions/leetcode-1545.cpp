/**
 * 1545. Find Kth Bit in Nth Binary String
 * 
 * Given two positive integers n and k, the binary string Sn is formed as follows:
 * 
 * S1 = "0"
 * Si = Si-1 + "1" + reverse(invert(Si-1)) for i > 1
 * Where + denotes the concatenation operation, reverse(x) returns the reversed string x, and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).
 * 
 * For example, the first 4 strings in the above sequence are:
 * 
 * S1 = "0"
 * S2 = "011"
 * S3 = "0111001"
 * S4 = "011100110110001"
 * Return the kth bit in Sn. It is guaranteed that k is valid for the given n.
 * 
 * 
 * Example 1:
 * Input: n = 3, k = 1
 * Output: "0"
 * Explanation: S3 is "0111001". The 1st bit is "0".
 * 
 * Example 2:
 * Input: n = 4, k = 11
 * Output: "1"
 * Explanation: S4 is "011100110110001". The 11th bit is "1".
 * 
 * Example 3:
 * Input: n = 1, k = 1
 * Output: "0"
 * 
 * Example 4:
 * Input: n = 2, k = 3
 * Output: "1"
 * 
 * Constraints:
 * 1 <= n <= 20
 * 1 <= k <= 2^n - 1
 * 
 */
class Solution {
public:
    char findKthBit(int n, int k) {
        // Base case
        if (n == 1) return '0';
        
        int mid = 1 << (n - 1);  // 2^(n-1), the middle position (1-indexed)
        
        if (k == mid) {
            return '1';
        } else if (k < mid) {
            // The k-th bit lies in the first half (S_{n-1})
            return findKthBit(n - 1, k);
        } else {
            // The k-th bit lies in the second half (reverse(invert(S_{n-1})))
            // Find the mirrored position in S_{n-1}
            int mirrored = (1 << n) - k;   // because total length = 2^n - 1
            char bit = findKthBit(n - 1, mirrored);
            // Invert the bit
            return bit == '0' ? '1' : '0';
        }
    }
};