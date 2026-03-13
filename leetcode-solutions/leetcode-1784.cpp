/**
 * 1784. Check if Binary String Has at Most One Segment of Ones
 * 
 * Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one contiguous segment of ones. Otherwise, return false.
 * 
 * Example 1:
 * 
 * Input: s = "1001"
 * Output: false
 * Explanation: The ones do not form a contiguous segment.
 * 
 * Example 2:
 * 
 * Input: s = "110"
 * Output: true
 * 
 * Constraints:
 * 
 * 1 <= s.length <= 100
 * s[i]​​​​ is either '0' or '1'.
 * s[0] is ​​​​​'1'.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    bool checkOnesSegment(string s) {
        // 如果字符串中不存在 "01"，说明所有的1都是连续的
        return s.find("01") == string::npos;
    }
};