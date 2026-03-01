/**
 * 1311. Get Watched Videos by Your Friends
 * 
 * There are n people, each person has a unique id between 0 and n-1. Given the arrays watchedVideos and friends, where watchedVideos[i] and friends[i] contain the list of watched videos and the list of friends respectively for the person with id = i.
 * 
 * Level 1 of videos are all watched videos by your friends, level 2 of videos are all watched videos by the friends of your friends and so on. In general, the level k of videos are all watched videos by people with the shortest path exactly equal to k with you. Given your id and the level of videos, return the list of videos ordered by their frequencies (increasing). For videos with the same frequency order them alphabetically from least to greatest. 
 * 
 * Example 1:
 * Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
 * Output: ["B","C"] 
 * Explanation: 
 * You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
 * Person with id = 1 -> watchedVideos = ["C"] 
 * Person with id = 2 -> watchedVideos = ["B","C"] 
 * The frequencies of watchedVideos by your friends are: 
 * B -> 1 
 * C -> 2
 * 
 * Example 2:
 * Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
 * Output: ["D"]
 * Explanation: 
 * You have id = 0 (green color in the figure) and the only friend of your friends is the person with id = 3 (yellow color in the figure).
 * 
 * Note:
 * 1 <= n <= 100
 * 1 <= watchedVideos.length <= 100
 * 1 <= watchedVideos[i].length <= 100
 * 1 <= friends.length <= n
 * friends[i].length == n
 * 0 <= friends[i][j] < n
 * 0 <= id < n
 * 1 <= level < n
 * if friends[i][j] == id, then i == j
 * All watchedVideos[i] have unique values.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, 
                                          vector<vector<int>>& friends, 
                                          int id, int level) {
        int n = friends.size();
        // 步骤1：BFS 找到第 level 层的所有好友
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(id);
        visited[id] = true;
        
        int currentLevel = 0;
        while (!q.empty() && currentLevel < level) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                int person = q.front();
                q.pop();
                for (int friendId : friends[person]) {
                    if (!visited[friendId]) {
                        visited[friendId] = true;
                        q.push(friendId);
                    }
                }
            }
            currentLevel++;
        }
        
        // 如果没到指定层就结束了（理论上不会，因为 level < n）
        if (currentLevel < level) return {};
        
        // 步骤2：统计第 level 层好友观看的视频频率
        unordered_map<string, int> freq;
        int size = q.size(); // 当前队列中全是第 level 层的好友
        for (int i = 0; i < size; ++i) {
            int person = q.front();
            q.pop();
            for (const string& video : watchedVideos[person]) {
                freq[video]++;
            }
        }
        
        // 步骤3：将统计结果转为 vector 并按要求排序
        vector<pair<string, int>> videos(freq.begin(), freq.end());
        sort(videos.begin(), videos.end(), 
             [](const pair<string, int>& a, const pair<string, int>& b) {
                 if (a.second == b.second) {
                     return a.first < b.first; // 频率相同，按字母序
                 }
                 return a.second < b.second;   // 按频率升序
             });
        
        // 提取视频名称
        vector<string> result;
        for (const auto& p : videos) {
            result.push_back(p.first);
        }
        return result;
    }
};
