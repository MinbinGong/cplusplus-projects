/*
 * Design Log Storage System
 *
 * You are given several logs that each log contains a unique id and timestamp. Timestamp is a string that has the following format: Year:Month:Day:Hour:Minute:Second, for example, 2017:01:01:23:59:59. All domains are zero-padded decimal numbers.
 * 
 * Design a log storage system to implement the following functions:
 * 
 * void Put(int id, string timestamp): Given a log's unique id and timestamp, store the log in your storage system.
 * 
 * int[] Retrieve(String start, String end, String granularity): Return the id of logs whose timestamps are within the range from start to end. Start and end all have the same format as timestamp, and granularity means how precise the range should be (i.e. to the exact Day, Minute, etc.). For example, start = "2017:01:01:23:59:59", end = "2017:01:02:23:59:59", granularity = "Day" means that we need to find the logs within the inclusive range from Jan. 1st 2017 to Jan. 2nd 2017.
 * 
 * Example 1:
 * Input: 
 * put(1, "2017:01:01:23:59:59");
 * put(2, "2017:01:01:22:59:59");
 * put(3, "2016:01:01:00:00:00");
 * retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Year"); // return [1,2,3], because you need to return all logs within 2016 and 2017.
 * retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Month"); // return [1,2], because you need to return all logs within Jan. 2016 and Jan. 2017.
 * retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Day"); // return [1], because you need to return all logs within 2017.
 * 
 * Note:
 * There will be at most 300 operations of Put or Retrieve.
 * Year ranges from [2000,2017]. Hour ranges from [00,23].
 * Output for Retrieve has no order required.
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class LogSystem {
private:
    // 存储所有日志，每个元素是一个pair：(timestamp, id)
    vector<pair<string, int>> logs;
    // 粒度到截取长度的映射（字符串索引位置）
    unordered_map<string, int> granularityLen = {
        {"Year", 4},    // 年份占4个字符
        {"Month", 7},   // 年份4 + 分隔符1 + 月份2 = 7
        {"Day", 10},    // 再加分隔符1 + 日2 = 10
        {"Hour", 13},   // 再加分隔符1 + 时2 = 13
        {"Minute", 16}, // 再加分隔符1 + 分2 = 16
        {"Second", 19}  // 再加分隔符1 + 秒2 = 19
    };

public:
    LogSystem() {}
    
    void put(int id, string timestamp) {
        logs.emplace_back(timestamp, id);
    }
    
    vector<int> retrieve(string start, string end, string granularity) {
        int len = granularityLen[granularity];  // 需要比较的前缀长度
        string startPrefix = start.substr(0, len);
        string endPrefix = end.substr(0, len);
        
        vector<int> result;
        for (const auto& [ts, id] : logs) {
            string tsPrefix = ts.substr(0, len);
            // 字符串比较（因格式固定，字典序等价于时间序）
            if (startPrefix <= tsPrefix && tsPrefix <= endPrefix) {
                result.push_back(id);
            }
        }
        return result;
    }
};