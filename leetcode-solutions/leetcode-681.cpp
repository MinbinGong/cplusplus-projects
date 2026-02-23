/*
 * Next Closest Time
 *
 * Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no limit on how many times a digit can be reused.
 *
 * You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.
 * 
 * Example 1:
 *
 * Input: "19:34"
 * Output: "19:39"
 * Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours and 59 minutes later.
 * 
 * Example 2:
 *
 * Input: "23:59"
 * Output: "22:22"
 * Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22. It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.
 * 
 * Note:
 *
 * The given time is in the range of [00:00, 23:59].
 * The input time must be a valid time.
 * 
 */
#include <string>
#include <unordered_set>
using namespace std;

class Solution1 {
public:
    string nextClosestTime(string time) {
        // 提取所有出现的数字
        unordered_set<char> digits;
        for (char c : time) {
            if (c != ':') digits.insert(c);
        }
        
        // 将时间转换为分钟数
        int cur = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3, 2));
        
        // 从下一分钟开始尝试，最多尝试24小时
        for (int i = 1; i <= 1440; ++i) {
            int next = (cur + i) % 1440;  // 处理跨天
            int hour = next / 60;
            int minute = next % 60;
            
            // 格式化为两位数字符串
            string h = (hour < 10 ? "0" : "") + to_string(hour);
            string m = (minute < 10 ? "0" : "") + to_string(minute);
            
            // 检查是否所有字符都在允许的数字集合中
            bool valid = true;
            for (char c : h + m) {
                if (!digits.count(c)) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                return h + ":" + m;
            }
        }
        
        return time;  // 理论上不会执行到这里
    }
};

class Solution2 {
public:
    string nextClosestTime(string time) {
        // 收集所有出现的数字
        vector<int> digits;
        digits.push_back(time[0] - '0');
        digits.push_back(time[1] - '0');
        digits.push_back(time[3] - '0');
        digits.push_back(time[4] - '0');
        
        // 去重
        sort(digits.begin(), digits.end());
        digits.erase(unique(digits.begin(), digits.end()), digits.end());
        
        int curHour = (time[0] - '0') * 10 + (time[1] - '0');
        int curMin = (time[3] - '0') * 10 + (time[4] - '0');
        int curTotal = curHour * 60 + curMin;
        
        int bestDiff = 24 * 60;  // 最大可能差值
        string result = time;
        
        // 枚举所有可能的时和分组合
        for (int h1 : digits) {
            for (int h2 : digits) {
                int hour = h1 * 10 + h2;
                if (hour >= 24) continue;
                
                for (int m1 : digits) {
                    for (int m2 : digits) {
                        int minute = m1 * 10 + m2;
                        if (minute >= 60) continue;
                        
                        int total = hour * 60 + minute;
                        int diff = total - curTotal;
                        
                        // 处理跨天的情况（第二天的同一时间算24小时后）
                        if (diff <= 0) diff += 24 * 60;
                        
                        // 找到更接近的时间
                        if (diff > 0 && diff < bestDiff) {
                            bestDiff = diff;
                            result = (hour < 10 ? "0" : "") + to_string(hour) + ":" +
                                     (minute < 10 ? "0" : "") + to_string(minute);
                        }
                    }
                }
            }
        }
        
        return result;
    }
};

class Solution3 {
private:
    vector<int> digits;
    vector<int> currTime;
    int curMinutes;
    int bestMinutes;
    int minDiff;
    
    int toMinutes(int hour, int minute) {
        return hour * 60 + minute;
    }
    
    // 计算时间差（考虑跨天）
    int timeDiff(int t1, int t2) {
        if (t1 == t2) return 1440;  // 相同时间算第二天
        return ((1440 - t1) + t2) % 1440;
    }
    
    void dfs(int depth) {
        if (depth == 4) {
            int hour = currTime[0] * 10 + currTime[1];
            int minute = currTime[2] * 10 + currTime[3];
            
            // 验证合法性
            if (hour > 23 || minute > 59) return;
            
            int total = toMinutes(hour, minute);
            int diff = timeDiff(curMinutes, total);
            
            if (diff > 0 && diff < minDiff) {
                minDiff = diff;
                bestMinutes = total;
            }
            return;
        }
        
        for (int digit : digits) {
            currTime[depth] = digit;
            dfs(depth + 1);
        }
    }
    
public:
    string nextClosestTime(string time) {
        // 提取数字
        digits.clear();
        digits.push_back(time[0] - '0');
        digits.push_back(time[1] - '0');
        digits.push_back(time[3] - '0');
        digits.push_back(time[4] - '0');
        
        // 计算当前时间的分钟数
        int hour = (time[0] - '0') * 10 + (time[1] - '0');
        int minute = (time[3] - '0') * 10 + (time[4] - '0');
        curMinutes = toMinutes(hour, minute);
        
        currTime.resize(4);
        bestMinutes = curMinutes;
        minDiff = 1440;
        
        dfs(0);
        
        // 格式化为字符串
        int bestHour = bestMinutes / 60;
        int bestMin = bestMinutes % 60;
        return (bestHour < 10 ? "0" : "") + to_string(bestHour) + ":" +
               (bestMin < 10 ? "0" : "") + to_string(bestMin);
    }
};