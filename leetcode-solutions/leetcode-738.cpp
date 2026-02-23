/*
 * Monotone Increasing Digits
 *
 * Given a non-negative integer N, find the largest number that is less than or equal to N with monotone increasing digits.
 * 
 * (Recall that an integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.)
 * 
 * Note:
 * 1. N is an integer in the range [0, 10^9].
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string s = to_string(n);
        int marker = s.length(); // position from which to set all digits to 9
        
        // Scan from right to left to find the first decreasing pair
        for (int i = s.length() - 1; i > 0; --i) {
            if (s[i] < s[i - 1]) {
                marker = i;          // we need to set all digits from i to end to 9
                s[i - 1]--;          // decrease the previous digit
            }
        }
        
        // Set all digits from marker to end to '9'
        for (int i = marker; i < s.length(); ++i) {
            s[i] = '9';
        }
        
        return stoi(s);
    }
};
