/**
 * 1154. Day of the Year
 * Easy
 * 
 * (This problem is an interactive problem.)
 * 
 * Given a string date representing a Gregorian calendar date formatted as YYYY-MM-DD, return the day number of the year.
 * 
 * Example 1:
 * Input: date = "2019-01-09"
 * Output: 9
 * Explanation: Given date is the 9th day of the year in 2019.
 * 
 * Example 2:
 * Input: date = "2019-02-10"
 * Output: 41
 * 
 * Note:
 * date.length == 10
 * date[4] == date[7] == '-', and all other date[i]'s are digits
 * date represents a calendar date between Jan 1st, 1900 and Dec 31, 2019.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int dayOfYear(string date) {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        
        // 每个月的天数（非闰年）
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // 判断闰年
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap) {
            daysInMonth[1] = 29; // 二月改成29天
        }
        
        int total = 0;
        for (int i = 0; i < month - 1; ++i) {
            total += daysInMonth[i];
        }
        total += day;
        return total;
    }
};