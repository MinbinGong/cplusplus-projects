/*
 * 358. Rearrange String k Distance Apart
 *
 * Given a string s and an integer k, rearrange s such that the same characters are at least distance k from each other.
 * If it is not possible to rearrange the string, return an empty string "".
 * 
 * Example 1:
 * Input: s = "aabbcc", k = 3
 * Output: "abcabc"
 * Explanation: The same letters are at least a distance of 3 from each other.
 * 
 * Example 2:
 * Input: s = "aaabc", k = 3
 * Output: ""
 * Explanation: It is not possible to rearrange the string.
 * 
 * Example 3:
 * Input: s = "aaadbbcc", k = 2
 * Output: "abacabcd"
 * Explanation: The same letters are at least a distance of 2 from each other.
 * 
 * Constraints:
 * 1 <= s.length <= 3 * 105
 * s consists of only lowercase English letters.
 * 0 <= k <= s.length
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Solution1 {
public:
    string rearrangeString(string s, int k) {
        // 如果 k <= 1，任何顺序都满足要求
        if (k <= 1) return s;

        // 1. 统计每个字符的出现频率
        unordered_map<char, int> freq;
        for (char c : s) {
            freq[c]++;
        }

        // 2. 构建最大堆，按频率排序（pair<频率, 字符>）
        // 注意 C++ 的 priority_queue 默认是最大堆，但比较的是 pair 的第一个元素
        // 我们想让频率高的在堆顶，所以用 pair<int, char>，first 存频率
        priority_queue<pair<int, char>> maxHeap;
        for (auto& p : freq) {
            maxHeap.push({p.second, p.first});
        }

        // 3. 冷却队列，存放 (剩余次数, 字符)，用于强制间隔
        queue<pair<int, char>> coolDown;
        string result;

        // 4. 开始构建结果字符串
        while (!maxHeap.empty()) {
            // 取出当前频率最高的可用字符
            auto [count, ch] = maxHeap.top();
            maxHeap.pop();

            // 加入结果
            result.push_back(ch);
            count--;

            // 将使用后的字符放入冷却队列（剩余次数可能为 0）
            coolDown.push({count, ch});

            // 如果冷却队列长度达到 k，说明最早放入的那个字符已经过了 k 个位置
            // 可以重新放回堆中（如果还有剩余次数）
            if (coolDown.size() >= k) {
                auto [cnt, c] = coolDown.front();
                coolDown.pop();
                if (cnt > 0) {
                    maxHeap.push({cnt, c});
                }
            }
        }

        // 5. 检查是否全部字符都被成功放置
        return result.length() == s.length() ? result : "";
    }
};