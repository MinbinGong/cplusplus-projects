#include <set>
#include <map>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

class Twitter
{
    map<int, set<int>> followees;
    map<int, vector<pair<int, int>>> posts;
    vector<int> ans;
    int timestamp = 0;

public:
    /** Initialize your data structure here. */
    Twitter()
    {
    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId)
    {
        posts[userId].push_back({tweetId, timestamp});
        timestamp++;
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. 
        Each item in the news feed must be posted by users who the user followed or by the user herself. 
        Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId)
    {
        ans.clear();
        map<int, int> idx;
        priority_queue<pair<int, int>> pq;
        idx[userId] = posts[userId].size() - 1;
        if (idx[userId] >= 0)
            pq.push({posts[userId].back().second, userId});

        for (auto x : followees[userId])
        {
            if (!posts.count(x))
                continue;
            idx[x] = posts[x].size() - 1;
            if (idx[x] < 0)
                continue;
            pq.push({posts[x].back().second, x});
        }
        while (!pq.empty())
        {
            auto tp = pq.top();
            pq.pop();
            int user = tp.second;
            if (ans.size() == 10)
                break;
            ans.push_back(posts[user][idx[user]].first);
            idx[user]--;
            if (idx[user] >= 0)
            {
                pq.push({posts[user][idx[user]].second, user});
            }
        }
        return ans;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId)
    {
        if (followerId == followeeId)
            return;
        followees[followerId].insert(followeeId);
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId)
    {
        if (followees[followerId].count(followeeId))
            followees[followerId].erase(followeeId);
    }
};
