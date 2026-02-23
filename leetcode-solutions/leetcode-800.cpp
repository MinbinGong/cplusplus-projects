/*
 * 800. Similar RGB Color
 *
 * In the following, every capital letter represents some hexadecimal digit from 0 to f.
 * 
 * The red-green-blue color "#AABBCC" can be written as "#ABC" in shorthand.  For example, "#15c" is shorthand for the color "#1155cc".
 * 
 * Now, say the similarity between two colors "#ABCDEF" and "#UVWXYZ" is -(AB - UV)^2 - (CD - WX)^2 - (EF - YZ)^2.
 * 
 * Given the color "#ABCDEF", return a 7 character color that is most similar to #ABCDEF, and has a shorthand (that is, it can be represented as some "#XYZ"
 * 
 * Example 1:
 * Input: color = "#09f166"
 * Output: "#11ee66"
 * Explanation:  
 * The similarity is -(0x09 - 0x11)^2 -(0xf1 - 0xee)^2 - (0x66 - 0x66)^2 = -64 -9 -0 = -73.
 * 
 * Note:
 * 1. color is a string of length 7.
 * 2. color is a valid RGB color: for i > 0, color[i] is a hexadecimal digit from 0 to f
 * 3. Any answer which has the same (highest) similarity as the best answer will be accepted.
 * 4. All inputs and outputs should use lowercase letters, and the output is 7 characters.
 * 5. The similarity is defined above.
 * 
 */
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Solution {
public:
    string similarRGB(string color) {
        string res = "#";
        for (int i = 1; i < 7; i += 2) {
            string comp = color.substr(i, 2);
            int num = stoi(comp, nullptr, 16);
            // best digit such that d*17 is closest to num
            int d = (num + 8) / 17; // rounding to nearest integer
            if (d > 15) d = 15;
            char digit = d < 10 ? '0' + d : 'a' + (d - 10);
            res.push_back(digit);
            res.push_back(digit);
        }
        return res;
    }
};