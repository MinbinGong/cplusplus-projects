/*
 * 1185. Day of the Week
 * 
 * Given a date, return the corresponding day of the week for that date.
 * 
 * The input is given as three integers representing the day, month and year respectively.
 * 
 * Return the answer as one of the following values {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}.
 * 
 * Example 1:
 * 
 * Input: day = 31, month = 8, year = 2019
 * Output: "Saturday"
 * Example 2:
 * 
 * Input: day = 18, month = 7, year = 1999
 * Output: "Sunday"
 * Example 3:
 * 
 * Input: day = 15, month = 8, year = 1993
 * Output: "Sunday"
 * 
 * 
 * Constraints:
 * 
 * The given dates are valid dates between the years 1971 and 2100.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string dayOfTheWeek(int day, int month, int year) {
        // Base: 1971-01-01 was a Friday
        vector<string> weekdays = {"Sunday", "Monday", "Tuesday",
                                   "Wednesday", "Thursday", "Friday", "Saturday"};
        vector<int> monthDays = {31, 28, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};

        int totalDays = 0;

        // Add days from years 1971 to year-1
        for (int y = 1971; y < year; ++y) {
            totalDays += isLeap(y) ? 366 : 365;
        }

        // Add days from months January to month-1 of the current year
        for (int m = 1; m < month; ++m) {
            totalDays += monthDays[m - 1];
            if (m == 2 && isLeap(year)) {
                totalDays += 1; // February in leap year has 29 days
            }
        }

        // Add days of the current month (day starts from 1, so subtract 1)
        totalDays += day - 1;

        // 1971-01-01 was Friday (index 5)
        int weekday = (5 + totalDays) % 7;
        return weekdays[weekday];
    }

private:
    bool isLeap(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
};