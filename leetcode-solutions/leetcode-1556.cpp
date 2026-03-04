/**
 * 1556. Thousand Separator
 * 
 * Given an integer n, add a dot (".") as the thousands separator and return it in string format.
 * 
 * Example 1:
 * Input: n = 987
 * Output: "987"
 * 
 * Example 2:
 * Input: n = 1234
 * Output: "1.234"
 * 
 * Constraints:
 * 0 <= n <= 2^31 - 1
 * 
 */
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string thousandSeparator(int n) {
        // Handle negative numbers
        if (n < 0) {
            return "-" + thousandSeparator(-(long long)n);
        }
        
        string s = to_string(n);
        string res;
        int count = 0;
        
        // Build from the rightmost digit
        for (int i = s.size() - 1; i >= 0; --i) {
            res.push_back(s[i]);
            count++;
            // Insert dot after every three digits, but not after the first digit
            if (count % 3 == 0 && i != 0) {
                res.push_back('.');
            }
        }
        
        // Reverse to get the correct order
        reverse(res.begin(), res.end());
        return res;
    }
};
