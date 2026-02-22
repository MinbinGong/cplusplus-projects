/*
 * Student Attendance Record I
 *
 * You are given a string representing an attendance record for a student. The record only contains the following three characters:
 * 'A' : Absent.
 * 'L' : Late.
 * 'P' : Present.
 * A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).
 * 
 * You need to return whether the student could be rewarded according to his attendance record.
 * 
 * Example 1:
 * Input: "PPALLP"
 * Output: True
 * 
 * Example 2:
 * Input: "PPALLL"
 * Output: False
 * 
 * Note:
 * The length of the input string will be in range [1, 1000].
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    bool checkRecord(string s) {
        int absences = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'A') {
                absences++;
                if (absences >= 2) return false;
            }
            if (i >= 2 && s[i] == 'L' && s[i-1] == 'L' && s[i-2] == 'L') {
                return false;
            }
        }
        return true;
    }
};