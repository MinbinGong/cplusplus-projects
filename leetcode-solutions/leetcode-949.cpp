/*
 * Largest Time for Given Digits
 *
 * Given an array of 4 digits, return the largest 24 hour time that can be made.
 *
 * The smallest 24 hour time is 00:00, and the largest is 23:59.  Starting from 00:00, a time is larger if more time has elapsed since midnight.
 *
 * Return the answer as a string of length 5.  If no valid time can be made, return an empty string.
 * 
 * Example 1:
 * Input: [1,2,3,4]
 * Output: "23:41"
 * 
 * Example 2:
 * Input: [5,5,5,5]
 * Output: ""
 * 
 * Note:
 * A.length == 4
 * 0 <= A[i] <= 9
 * 
 */
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    string largestTimeFromDigits(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        string best;
        do {
            int hour = arr[0] * 10 + arr[1];
            int minute = arr[2] * 10 + arr[3];
            if (hour < 24 && minute < 60) {
                string cur = to_string(arr[0]) + to_string(arr[1]) + ":" + to_string(arr[2]) + to_string(arr[3]);
                if (cur > best) best = cur;
            }
        } while (next_permutation(arr.begin(), arr.end()));
        return best;
    }
};