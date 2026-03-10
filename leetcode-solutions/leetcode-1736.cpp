/**
 * 1736. Latest Time by Replacing Hidden Digits
 * 
 * You are given a string time in the form of hh:mm, where some of the digits in the string are hidden (represented by ?).
 * The valid times are those inclusively between 00:00 and 23:59.
 * Return the latest valid time you can get from time by replacing the hidden digits.
 * 
 * Example 1:
 * Input: time = "2?:?0"
 * Output: "23:50"
 * Explanation: The latest hour beginning with the digit '2' is 23 and the latest minute ending with the digit '0' is 50.
 * 
 * Example 2:
 * Input: time = "0?:3?"
 * Output: "09:39"
 * 
 * Example 3:
 * Input: time = "1?:22"
 * Output: "19:22"
 * 
 * Constraints:
 * time is in the format hh:mm.
 * It is guaranteed that some of the digits in time are hidden (represented by ?).
 * 
 */
class Solution {
public:
    string maximumTime(string time) {
        // 处理小时第一位
        if (time[0] == '?') {
            // 如果第二位是'?'或者小于等于3，第一位可以取'2'，否则只能取'1'
            time[0] = (time[1] == '?' || time[1] <= '3') ? '2' : '1';
        }
        // 处理小时第二位
        if (time[1] == '?') {
            // 如果第一位是'2'，第二位最大为'3'，否则为'9'
            time[1] = (time[0] == '2') ? '3' : '9';
        }
        // 处理分钟第一位
        if (time[3] == '?') {
            time[3] = '5';
        }
        // 处理分钟第二位
        if (time[4] == '?') {
            time[4] = '9';
        }
        return time;
    }
};