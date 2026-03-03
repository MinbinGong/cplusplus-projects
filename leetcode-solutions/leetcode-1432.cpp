/*
 * 1432. Max Difference You Can Get From Changing an Integer
 *
 * You are given an integer num. You will apply the following steps exactly two times:
 * 
 * Pick a digit x (0 <= x <= 9).
 * Pick another digit y (0 <= y <= 9). The digit y can be equal to x.
 * Replace all the occurrences of x in the decimal representation of num by y.
 * The new integer cannot have any leading zeros, also the new integer cannot be 0.
 * Let a and b be the results of applying the operations to num the first and second times, respectively.
 * 
 * Return the max difference between a and b.
 * 
 * Example 1:
 * 
 * Input: num = 555
 * Output: 888
 * Explanation: The first time pick x = 5 and y = 9 and store the new integer in a.
 * The second time pick x = 5 and y = 1 and store the new integer in b.
 * Thus we have a = 999 and b = 111 and max difference = 888
 * 
 * Example 2:
 * 
 * Input: num = 9
 * Output: 8
 * Explanation: The first time pick x = 9 and y = 9 and store the new integer in a.
 * The second time pick x = 9 and y = 1 and store the new integer in b.
 * Thus we have a = 9 and b = 1 and max difference = 8
 * 
 * Example 3:
 * 
 * Input: num = 123456
 * Output: 820000
 * 
 * Example 4:
 * 
 * Input: num = 10000
 * Output: 80000
 * 
 * Example 5:
 * 
 * Input: num = 9288
 * Output: 8700
 * 
 * Note:
 * 2 <= num <= 10^8
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int maxDiff(int num) {
        string s = to_string(num);
        string maxStr = s;
        // Maximize: find the leftmost digit that is not '9'
        // and replace all its occurrences with '9'
        for (char c : s) {
            if (c != '9') {
                char target = c;
                for (char &ch : maxStr) {
                    if (ch == target) ch = '9';
                }
                break;
            }
        }

        string minStr = s;
        // Minimize: two cases
        if (s[0] != '1') {
            // If the first digit is greater than '1', replace all its occurrences with '1'
            // (if it's '0', we do nothing because that only happens for num == 0)
            if (s[0] > '1') {
                char target = s[0];
                for (char &ch : minStr) {
                    if (ch == target) ch = '1';
                }
            }
        } else {
            // First digit is '1': find the first later digit that is not '0' and not '1'
            // and replace all its occurrences with '0'
            for (int i = 1; i < s.size(); ++i) {
                if (s[i] != '0' && s[i] != '1') {
                    char target = s[i];
                    for (char &ch : minStr) {
                        if (ch == target) ch = '0';
                    }
                    break;
                }
            }
        }

        return stoi(maxStr) - stoi(minStr);
    }
};