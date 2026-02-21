/*
 * Magic String
 *
 * A magic string is a string that consists of only 'a' and 'b' and obeys the following rules:
 *
 * The string is empty, or
 * The string can be AB, where A and B are magic strings, or
 * The string can be BA, where A and B are magic strings.
 *
 * Given a positive integer n, return the number of magic strings of length n.
 *
 * Constraints:
 * 1 <= n <= 105
 *
 */
#include <string>
using namespace std;

class Solution {
public:
    int magicalString(int n) {
        if (n == 0) return 0;
        // The first three characters are "122"
        if (n <= 3) return 1; 

        string s = "122";          // start with the known beginning
        int i = 2;                  // index to read next group size
        char nextChar = '1';        // the character to be added next (alternates)

        // generate until we have at least n characters
        while (s.size() < n) {
            int repeat = s[i] - '0';   // size of the next group
            char ch = nextChar;         // character to repeat
            s.append(repeat, ch);       // append that character 'repeat' times
            ++i;                        // move to the next group indicator
            nextChar = (ch == '1') ? '2' : '1'; // flip for the next group
        }

        // count the number of '1's in the first n characters
        int cnt = 0;
        for (int j = 0; j < n; ++j) {
            if (s[j] == '1') ++cnt;
        }
        return cnt;
    }
};