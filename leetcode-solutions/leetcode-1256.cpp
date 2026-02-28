/*
 * 1256. Encode Number
 *
 * Given a non-negative integer num, Return its encoding string.
 *
 * The encoding is done by converting the integer to a string using a secret function that you should deduce from the following table:
 *
 * Example 1:
 * Input: num = 23
 * Output: "1000"
 *
 * Example 2:
 * Input: num = 107
 * Output: "101100"
 *
 * Constraints:
 * 0 <= num <= 10^9
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string encode(int num) {
        if (num == 0) return "";
        int x = num + 1;
        string ans;
        while (x > 1) {
            ans = (x % 2 == 0 ? '0' : '1') + ans;
            x >>= 1;
        }
        return ans;
    }
};