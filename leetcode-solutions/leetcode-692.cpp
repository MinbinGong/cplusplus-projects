/*
 * Top K Frequent Words
 *
 * Given a non-empty list of words, return the k most frequent elements.
 *
 * Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, then the word with the lower alphabetical order comes first.
 *
 * Example 1:
 *
 * Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
 * Output: ["i", "love"]
 * Explanation: "i" and "love" are the two most frequent words.
 *     Note that "i" comes before "love" due to a lower alphabetical order.
 * 
 * Note:
 *
 * You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
 * Input words contain only lowercase letters.
 * 
 * Follow up:
 *
 * Try to solve it in O(n log k) time and O(n) extra space.
 * 
 */
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        // 统计每个单词的频率
        unordered_map<string, int> freq;
        for (const string& word : words) {
            freq[word]++;
        }

        // 自定义比较器：频率小的优先级高（堆顶），频率相同时字典序大的优先级高
        auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);

        // 遍历所有单词，维护大小为k的最小堆
        for (const auto& entry : freq) {
            pq.push(entry);
            if (pq.size() > k) {
                pq.pop();
            }
        }

        // 从堆中取出结果，此时顺序是频率从小到大、字典序从大到小
        vector<string> result;
        while (!pq.empty()) {
            result.push_back(pq.top().first);
            pq.pop();
        }
        // 反转得到频率从高到低、字典序从小到大
        reverse(result.begin(), result.end());
        return result;
    }
};