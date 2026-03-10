/**
 * 1683. Invalid Tweets
 * 
 * Table: Tweets
 * 
 * +----------------+---------+
 * | Column Name    | Type    |
 * +----------------+---------+
 * | tweet_id       | int     |
 * | content        | varchar |
 * +----------------+---------+
 * tweet_id is the primary key for this table.
 * content is the full text of the tweet with a maximum length of 140.
 * 
 * Write an SQL query to find the IDs of the invalid tweets. The tweet is invalid if the number of characters used in the content of the tweet is strictly greater than 140.
 * 
 * Return the result table in any order.
 * 
 * The query result format is in the following example.
 * 
 * Example 1:
 * Input: 
 * Tweets table:
 * +----------+----------------------------------+
 * | tweet_id | content                          |
 * +----------+----------------------------------+
 * | 1        | Vote for Biden                   |
 * | 2        | Let us make America great again! |
 * +----------+----------------------------------+
 * Output: 
 * +----------+
 * | tweet_id |
 * +----------+
 * | 2        |
 * +----------+
 * Explanation: 
 * Tweet 1 has length = 14. It is a valid tweet.
 * Tweet 2 has length = 32. It is an invalid tweet.
 * 
 * Example 2:
 * Input: 
 * Tweets table:
 * +----------+----------------------------------+
 * | tweet_id | content                          |
 * +----------+----------------------------------+
 * | 3        | I love LeetCode!                |
 * +----------+----------------------------------+
 * Output: 
 * +----------+
 * | tweet_id |
 * +----------+
 * | 3        |
 * +----------+
 * Explanation: 
 * Tweet 3 has length = 18. It is a valid tweet.
 * 
 * Constraints:
 * 1 <= tweet_id <= 100
 * 1 <= content.length <= 140
 * 
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> invalidTweets(vector<pair<int, string>>& tweets) {
        vector<int> result;
        for (const auto& tweet : tweets) {
            if (tweet.second.length() > 15) {
                result.push_back(tweet.first);
            }
        }
        return result;
    }
};