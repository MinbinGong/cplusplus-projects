/*
 * 846. Hand of Straights
 * 
 * Alice has a hand of cards, given as an array of integers.
 * 
 * Now she wants to rearrange the cards into groups so that each group is size W, and consists of W consecutive cards.
 * 
 * Return true if and only if she can.
 * 
 * Example 1:
 * Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
 * Output: true
 * Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].
 * 
 * Example 2:
 * Input: hand = [1,2,3,4,5], W = 4
 * Output: false
 * Explanation: Alice's hand can't be rearranged into groups of 4.
 * 
 * Note:
 * 1 <= hand.length <= 10000
 * 0 <= hand[i] <= 10^9
 * 1 <= W <= hand.length
 * 
 */
#include <vector>
#include <map>

class Solution {
public:
    bool isNStraightHand(std::vector<int>& hand, int groupSize) {
        int n = hand.size();
        if (n % groupSize != 0) return false;

        // 统计每个数字出现的次数
        std::map<int, int> count;
        for (int card : hand) {
            count[card]++;
        }

        // 遍历所有数字（按键升序）
        for (auto it = count.begin(); it != count.end(); ++it) {
            int num = it->first;
            int freq = it->second;
            if (freq == 0) continue;

            // 尝试以 num 开头组成一组大小为 groupSize 的顺子
            for (int i = 0; i < groupSize; ++i) {
                int cur = num + i;
                if (count[cur] < freq) {
                    return false; // 频次不足
                }
                count[cur] -= freq;
            }
        }
        return true;
    }
};