/*
 * 1604. Alert Using Same Key-Card Three or More Times in a One Hour Period
 *
 * LeetCode company workers use key-cards to unlock office doors. Each time a worker uses their key-card, the security system saves the worker's name and the time when it was used. The system emits an alert if any worker uses the key-card three or more times in a one-hour period.
 *
 * You are given a list of strings keyName and keyTime where [keyName[i], keyTime[i]] corresponds to a person's name and the time when their key-card was used in a single day.
 *
 * Access times are given in the 24-hour time format "HH:MM", such as "23:51" and "09:49".
 *
 * Return a list of unique worker names who received an alert for frequent keycard use. Sort the names in ascending order alphabetically.
 *
 * Example 1:
 * Input: keyName = ["daniel","daniel","daniel","luis","luis","luis","luis"], keyTime = ["10:00","10:40","11:00","09:00","11:00","13:00","15:00"]
 * Output: ["daniel"]
 * Explanation: "daniel" used the keycard 3 times in a one-hour period ("10:00","10:40", "11:00").
 * 
 * Example 2:
 * Input: keyName = ["alice","alice","alice","bob","bob","bob","bob"], keyTime = ["12:01","12:00","18:00","21:00","21:20","21:30","23:00"]
 * Output: ["bob"]
 * Explanation: "bob" used the keycard 3 times in a one-hour period ("21:00","21:20", "21:30").
 * 
 * Example 3:
 * Input: keyName = ["john","john","john"], keyTime = ["23:58","23:59","00:01"]
 * Output: []
 * Explanation: "john" used the keycard 3 times in a one-hour period ("23:58","23:59", "00:01").
 * 
 * Constraints:
 * 1 <= keyName.length, keyTime.length <= 105
 * keyName.length == keyTime.length
 * keyTime are in the format "HH:MM".
 * Each keyName[i] contains only lowercase English letters.
 * It is guaranteed that each keyTime[i] corresponds to a unique worker in keyName.
 * 1 <= keyName[i].length <= 10
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        unordered_map<string, vector<int>> records;
        int n = keyName.size();
        for (int i = 0; i < n; ++i) {
            // 将时间转换为分钟数
            int hour = stoi(keyTime[i].substr(0, 2));
            int minute = stoi(keyTime[i].substr(3, 2));
            int total = hour * 60 + minute;
            records[keyName[i]].push_back(total);
        }

        vector<string> result;
        for (auto& [name, times] : records) {
            sort(times.begin(), times.end());
            // 检查是否有任意连续三次时间间隔 ≤ 60 分钟
            for (int i = 0; i + 2 < times.size(); ++i) {
                if (times[i + 2] - times[i] <= 60) {
                    result.push_back(name);
                    break;
                }
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};