/*
 * 362. Design Hit Counter
 *
 * Design a hit counter which counts the number of hits received in the past 5 minutes.
 * 
 * Each function accepts a timestamp parameter (in seconds granularity) and you may assume that calls are being made to the system in chronological order (ie, the timestamp is monotonically increasing). You may assume that the earliest timestamp starts at 1.
 * It is possible that several hits arrive roughly at the same time.
 * 
 */
#include <vector>
using namespace std;

// 每个槽位记录最近300秒内的命中次数和时间戳
class HitCounter {
private:
    vector<int> hits;   // 每个槽位的命中次数
    vector<int> times;  // 每个槽位对应的时间戳
public:
    /** Initialize your data structure here. */
    HitCounter() {
        hits.resize(300, 0);
        times.resize(300, 0);
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        int idx = timestamp % 300;
        if (times[idx] != timestamp) {
            // 新的一秒，重置计数
            times[idx] = timestamp;
            hits[idx] = 1;
        } else {
            // 同一秒内多次命中
            hits[idx]++;
        }
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        int total = 0;
        for (int i = 0; i < 300; ++i) {
            if (timestamp - times[i] < 300) {
                total += hits[i];
            }
        }
        return total;
    }
};