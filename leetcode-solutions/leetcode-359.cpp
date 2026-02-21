/*
 * 359. Logger Rate Limiter
 *
 * Design a logger system that receives a stream of messages along with their timestamps.
 * Each unique message should only be printed at most every 10 seconds (i.e. a message printed at timestamp t will prevent other identical messages from being printed until timestamp t + 10).
 * 
 * All messages will come in chronological order. Several messages may arrive at the same timestamp.
 * 
 * Implement the Logger class:
 * 
 * Logger() Initializes the logger object.
 * bool shouldPrintMessage(int timestamp, string message) Returns true if the message should be printed in the given timestamp, otherwise returns false.
 * 
 */
#include <unordered_map>
#include <string>
using namespace std;

class Logger {
private:
    unordered_map<string, int> lastPrinted; // 记录每个消息上一次打印的时间戳
public:
    Logger() {}
    
    bool shouldPrintMessage(int timestamp, string message) {
        // 如果消息从未打印过，或者距离上次打印已超过10秒，则允许打印
        if (lastPrinted.find(message) == lastPrinted.end() || timestamp - lastPrinted[message] >= 10) {
            lastPrinted[message] = timestamp;
            return true;
        }
        return false;
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */