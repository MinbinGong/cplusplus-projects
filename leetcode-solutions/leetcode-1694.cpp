/*
 * 1694. Reformat Phone Number
 *
 * You are given a phone number as a string number. number consists of digits, spaces ' ', and/or dashes '-'.
 * You would like to reformat the phone number in a certain manner. Firstly, remove all spaces and dashes. Then, group the digits from left to right into blocks of length 3 until there are 4 or fewer digits. The final digits are then grouped as follows:
 * 2 digits: A single block of length 2.
 * 3 digits: A single block of length 3.
 * 4 digits: Two blocks of length 2 each.
 * 
 * Given number, return the reformatted phone number.
 * 
 * Example 1:
 * Input: number = "1-23-45 6"
 * Output: "123-456"
 * Explanation: The digits are "123456".
 * Step 1: There are more than 4 digits, so group the next 3 digits. The 1st block is "123".
 * Step 2: There are 3 digits remaining, so put them in a single block of length 3. The 2nd block is "456".
 * Joining the blocks gives "123-456".
 * 
 * Example 2:
 * Input: number = "123 4-567"
 * Output: "123-45-67"
 * Explanation: The digits are "1234567".
 * Step 1: There are more than 4 digits, so group the next 3 digits. The 1st block is "123".
 * Step 2: There are 4 digits remaining, so split them into two blocks of length 2. The blocks are "45" and "67".
 * Joining the blocks gives "123-45-67".
 * 
 * Constraints:
 * 2 <= number.length <= 100
 * number consists of digits and the characters '-' and ' '.
 * There are at least two digits in number.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string reformatNumber(string number) {
        // 第一步：删除所有空格和破折号
        string digits;
        for (char c : number) {
            if (c >= '0' && c <= '9') {
                digits.push_back(c);
            }
        }
        
        string result;
        int n = digits.size();
        int i = 0;
        
        // 第二步：每3个一组分块，直到剩下4个或更少数字
        while (n - i > 4) {
            result += digits.substr(i, 3) + "-";
            i += 3;
        }
        
        // 第三步：处理最后4个或更少的数字
        if (n - i == 4) {
            result += digits.substr(i, 2) + "-" + digits.substr(i + 2, 2);
        } else {
            result += digits.substr(i);
        }
        
        return result;
    }
};