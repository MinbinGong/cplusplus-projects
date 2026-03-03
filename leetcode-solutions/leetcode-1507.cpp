/**
 * 1507. Reformat Date
 * 
 * Given a date string in the form Day Month Year, where:
 * Day is in the set {"1st", "2nd", "3rd", "4th", ..., "30th", "31st"}.
 * Month is in the set {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}.
 * Year is in the range [1900, 2100].
 * Convert the date string to the format YYYY-MM-DD, where:
 * YYYY denotes the 4 digit year.
 * MM denotes the 2 digit month.
 * DD denotes the 2 digit day.
 * 
 * Example 1:
 * Input: date = "20th Oct 2052"
 * Output: "2052-10-20"
 * 
 * Example 2:
 * Input: date = "6th Jun 1933"
 * Output: "1933-06-06"
 * 
 * Example 3:
 * Input: date = "26th May 1960"
 * Output: "1960-05-26"
 * 
 * Note:
 * The given dates are guaranteed to be valid, so no error handling is necessary.
 * 
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

class Solution {
public:
    string reformatDate(string date) {
        vector<string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                               "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        unordered_map<string, string> monthMap;
        
        for (int i = 0; i < 12; i++) {
            monthMap[months[i]] = (i < 9) ? "0" + to_string(i + 1) : to_string(i + 1);
        }
        
        stringstream ss(date);
        string day, month, year;
        ss >> day >> month >> year;
        
        // 提取日
        day = day.substr(0, day.size() - 2);
        if (day.size() == 1) day = "0" + day;
        
        return year + "-" + monthMap[month] + "-" + day;
    }
};