/**
 * 1348. Tweet Counts Per Frequency
 * 
 * A social media company is trying to monitor activity on their site by analyzing the number of tweets that occur in select periods of time. These periods can be partitioned into smaller time chunks based on a certain frequency (every minute, hour, or day).
 * 
 * For example, the period [10, 10000] (in seconds) would be partitioned into the following time chunks with these frequencies:
 * Every minute (60-second chunks): [10,69], [70,129], [130,189], ..., [9970,10000]
 * Every hour (3600-second chunks): [10,3609], [3610,7209], [7210,10000]
 * Every day (86400-second chunks): [10,10000]
 * 
 * Note that the last chunk may be shorter than the specified frequency's chunk size and will always end with the end time of the period (10000 in the above example).
 * 
 * Design and implement an API to help the company with their analysis.
 * 
 * Implement the TweetCounts class:
 * TweetCounts() Initializes the TweetCounts object.
 * void recordTweet(String tweetName, int time) Stores the tweetName at the recorded time (in seconds).
 * List<Integer> getTweetCountsPerFrequency(String freq, String tweetName, int startTime, int endTime) Returns a list of integers representing the number of tweets with tweetName in each time chunk for the given period of time [startTime, endTime] (in seconds) and frequency freq.
 * freq is one of "minute", "hour", or "day" representing a frequency of every minute, hour, or day respectively.
 * 
 * Example:
 * Input
 * ["TweetCounts","recordTweet","recordTweet","recordTweet","getTweetCountsPerFrequency","getTweetCountsPerFrequency","recordTweet","getTweetCountsPerFrequency"]
 * [[],["tweet3",0],["tweet3",60],["tweet3",10],["minute","tweet3",0,59],["minute","tweet3",0,60],["tweet3",120],["hour","tweet3",0,210]]
 * Output
 * [null,null,null,null,[2],[2,1],null,[4]]
 * 
 * Explanation
 * TweetCounts tweetCounts = new TweetCounts();
 * tweetCounts.recordTweet("tweet3", 0);
 * tweetCounts.recordTweet("tweet3", 60);
 * tweetCounts.recordTweet("tweet3", 10);                             // All tweets correspond to "tweet3" with recorded times at 0, 10 and 60.
 * tweetCounts.getTweetCountsPerFrequency("minute", "tweet3", 0, 59); // return [2]. The frequency is per minute (60 seconds), so there is one interval of time: 1) [0, 60> - > 2 tweets
 * tweetCounts.getTweetCountsPerFrequency("minute", "tweet3", 0, 60); // return [2, 1]. The frequency is per minute (60 seconds), so there are two intervals of time: 1) [0, 60> - > 2 tweets and 2) [60,61> - > 1 tweet
 * tweetCounts.recordTweet("tweet3", 120);                            // All tweets correspond to "tweet3" with recorded times at 0, 10, 60 and 120.
 * 
 * Note:
 * 0 <= time, startTime, endTime <= 10^9
 * 0 <= endTime - startTime <= 10^4
 * There will be at most 104 calls in total to recordTweet and getTweetCountsPerFrequency.
 * 
 */
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
using namespace std;

class TweetCounts {
private:
    unordered_map<string, multiset<int>> tweets;  // user -> sorted timestamps

public:
    TweetCounts() {}

    void recordTweet(string tweetName, int time) {
        tweets[tweetName].insert(time);
    }

    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
        int delta;
        if (freq == "minute") delta = 60;
        else if (freq == "hour") delta = 3600;
        else delta = 86400; // day

        vector<int> result;
        auto& ms = tweets[tweetName];
        if (ms.empty()) return result; // no tweets for this user

        // number of intervals = ceil((endTime - startTime) / delta)
        int intervals = (endTime - startTime + delta - 1) / delta;

        for (int i = 0; i < intervals; ++i) {
            int left = startTime + i * delta;
            int right = startTime + (i + 1) * delta;

            auto it_l = ms.lower_bound(left);
            auto it_r = ms.lower_bound(right);
            result.push_back(distance(it_l, it_r)); // count in [left, right)
        }

        return result;
    }
};