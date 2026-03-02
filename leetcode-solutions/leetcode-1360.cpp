/*
 * 1360. Number of Days Between Two Dates
 *
 * Write a program to count the number of days between two dates.
 * 
 * The two dates are given as strings, their format is YYYY-MM-DD as shown in the examples.
 * 
 * Example 1:
 * Input: date1 = "2019-06-29", date2 = "2019-06-30"
 * Output: 1
 * 
 * Example 2:
 * Input: date1 = "2020-01-15", date2 = "2019-12-31"
 * Output: 15
 * 
 * Note:
 * The given dates are valid dates between the years 1971 and 2100.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int daysBetweenDates(string date1, string date2) {
        return abs(daysSinceEpoch(date1) - daysSinceEpoch(date2));
    }

private:
    int daysSinceEpoch(string date) {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));

        // days in each month for a common year
        vector<int> monthDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // adjust February if leap year
        if (isLeap(year)) monthDays[1] = 29;

        int total = 0;
        // count days from year 1971 to year-1
        for (int y = 1971; y < year; ++y) {
            total += isLeap(y) ? 366 : 365;
        }
        // add days from months before the current month
        for (int m = 1; m < month; ++m) {
            total += monthDays[m - 1];
        }
        // add days in current month
        total += day;
        return total;
    }

    bool isLeap(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
};