/*
 * K Empty Slots
 *
 * You have N bulbs in a row numbered from 1 to N. Initially, all the bulbs are turned off. We turn on exactly one bulb everyday until all bulbs are on after N days.
 *
 * You are given an array bulbs of length N where bulbs[i] = x means that on the (i+1)th day, we will turn on the bulb at position x where i is 0-indexed and x is 1-indexed.
 *
 * Given an integer K, find out the minimum day number such that there exists two turned on bulbs that have exactly K bulbs between them that are all turned off.
 *
 * If there isn't such day, return -1.
 * 
 * Example 1:
 *
 * Input: bulbs = [1,3,2], K = 1
 * Output: 2
 * Explanation: On the first day: bulbs[0] = 1, first bulb is turned on: [1,0,0]
 * On the second day: bulbs[1] = 3, third bulb is turned on: [1,0,1]
 * On the third day: bulbs[2] = 2, second bulb is turned on: [1,1,1]
 * We return 2 because on the second day, there were two on bulbs with one off bulb between them.
 * 
 * Example 2:
 *
 * Input: bulbs = [1,2,3], K = 1
 * Output: -1
 * 
 * Note:
 *
 * N will be in the range [2, 20000].
 * K will be in the range [0, N-1].
 * bulbs[i] will be in the range [1, N] and be all unique.
 * 
 */
#include <string>
#include <vector>
#include <set>
using namespace std;

class Solution1 {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        set<int> bloom; // 存储已开花的位置（有序）
        for (int i = 0; i < flowers.size(); ++i) {
            int pos = flowers[i];
            bloom.insert(pos);
            
            // 检查后一个开花位置
            auto it = bloom.find(pos);
            if (next(it) != bloom.end() && *next(it) == pos + k + 1) {
                return i + 1; // 天数从1开始
            }
            
            // 检查前一个开花位置
            if (it != bloom.begin() && *prev(it) == pos - k - 1) {
                return i + 1;
            }
        }
        return -1;
    }
};

class Solution2 {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        int n = flowers.size();
        if (n == 0 || k >= n) return -1;
        
        // days[i] 表示在位置 i+1 开花的天数
        vector<int> days(n);
        for (int i = 0; i < n; ++i) {
            days[flowers[i] - 1] = i + 1;
        }
        
        int left = 0, right = k + 1;
        int result = INT_MAX;
        
        for (int i = 0; right < n; ++i) {
            if (days[i] < days[left] || days[i] <= days[right]) {
                if (i == right) {
                    // 窗口内的所有花都比两端开得晚，满足条件
                    result = min(result, max(days[left], days[right]));
                }
                // 窗口失效，从当前 i 开始新窗口
                left = i;
                right = i + k + 1;
            }
        }
        
        return result == INT_MAX ? -1 : result;
    }
};