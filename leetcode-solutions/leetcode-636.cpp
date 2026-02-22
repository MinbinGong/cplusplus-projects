/*
 * Exclusive Time of Functions
 * 
 * Given the number of functions n and a list of logs, each log logs[i] is a string with this format: "{function_id}:{"start" | "end"}:{timestamp}". For example, "0:start:3" means the function with id 0 starts from the very beginning of time 3. "1:end:2" means the function with id 1 ends at time 2.
 * 
 * Note that a function can be called multiple times, possibly recursively.
 * 
 * A function's exclusive time is the sum of execution times for all calls in the program. For example, if a function is called twice, one call executing for 2 time units and another call executing for 1 time unit, the exclusive time is 2 + 1 = 3.
 * 
 * Return the exclusive time of each function, sorted by their function id.
 * 
 * Example 1:
 * Input: n = 2, logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
 * Output: [3,4]
 * Explanation:
 * Function 0 starts at the beginning of time 0, executes 2 units of time, and recursively calls function 1.
 * Function 1 starts at the beginning of time 2, executes 4 units of time, and ends at the end of time 5.
 * Function 0 resumes execution at the beginning of time 6, executes 1 unit of time, and ends at the end of time 6,
 * thus executing for 1 unit of time.
 * So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.
 * 
 * Note:
 * 1 <= n <= 100
 * 1 <= logs.length <= 500
 * 0 <= function_id < n
 * 0 <= timestamp <= 109
 * No two start events will happen at the same timestamp.
 * No two end events will happen at the same timestamp.
 * Each function has an "end" log for each "start" log.
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> res(n, 0);
        stack<pair<int, int>> stk; // {function id, start time}
        int prevTime = 0;
        
        for (const string& log : logs) {
            // 解析日志
            size_t pos1 = log.find(':');
            size_t pos2 = log.find(':', pos1 + 1);
            int id = stoi(log.substr(0, pos1));
            string type = log.substr(pos1 + 1, pos2 - pos1 - 1);
            int time = stoi(log.substr(pos2 + 1));
            
            if (type == "start") {
                if (!stk.empty()) {
                    // 当前有正在运行的函数，将前一段空闲时间累加给栈顶函数
                    res[stk.top().first] += time - prevTime;
                }
                stk.push({id, time});
                prevTime = time;
            } else { // "end"
                auto [funcId, startTime] = stk.top();
                stk.pop();
                res[funcId] += time - startTime + 1;
                prevTime = time + 1; // 结束后的下一个时刻
            }
        }
        return res;
    }
};