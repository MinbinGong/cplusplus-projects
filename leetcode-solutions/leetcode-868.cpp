/**
 * 868. Binary Gap
 * 
 * Example 1:
 * Input: 22
 * Output: 2
 * Explanation: 
 * 22 in binary is 0b10110.
 * In the binary representation of 22, there are three ones, and two consecutive pairs of 1's.
 * The first consecutive pair of 1's have distance 2.
 * The second consecutive pair of 1's have distance 1.
 * The answer is the largest of these two distances, which is 2.
 * 
 * Example 2:
 * Input: 5
 * Output: 2
 * Explanation: 
 * 5 in binary is 0b101.
 * 
 * Example 3:
 * Input: 6
 * Output: 1
 * Explanation: 
 * 6 in binary is 0b110.
 * 
 * Example 4:
 * Input: 8
 * Output: 0
 * Explanation: 
 * 8 in binary is 0b1000.
 * 
 * Note:
 * 1 <= N <= 10^9
 * 
 */
#include <algorithm>
using namespace std;

class Solution {
public:
    int binaryGap(int N) {
        int last = -1; // 上一个1的位置
        int ans = 0;
        for (int i = 0; N > 0; ++i, N >>= 1) {
            if (N & 1) { // 当前位是1
                if (last != -1) {
                    ans = max(ans, i - last);
                }
                last = i;
            }
        }
        return ans;
    }
};