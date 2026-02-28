/**
 * 1224. Maximum Equal Frequency
 *
 * Given an array nums of positive integers, return the longest possible length of an array prefix of nums, such that it is possible to remove exactly one element from this prefix so that every number that has appeared in it will have the same number of occurrences.
 *
 * If after removing one element there are no remaining elements, it's still considered that every appeared number has the same number of ocurrences (0).
 *
 *
 *
 * Example 1:
 *
 * Input: nums = [2,2,1,1,5,3,3,5]
 * Output: 7
 * Explanation: For the subarray [2,2,1,1,5,3,3] of length 7, if we remove nums[4]=5, we will get [2,2,1,1,3,3], so that each number will appear exactly twice.
 *
 * Example 2:
 *
 * Input: nums = [1,1,1,2,2,2,3,3,3,4,4,4,5]
 * Output: 13
 *
 *
 * Constraints:
 *
 * 2 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^5
 *
 */
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        // freq: 记录每个数字出现的频率
        // count: 记录每个频率出现的次数
        unordered_map<int, int> freq, count;
        int maxFreq = 0;  // 当前最大频率
        int result = 0;
        
        for (int i = 0; i < nums.size(); ++i) {
            int num = nums[i];
            
            // 更新频率统计
            if (freq[num] > 0) {
                count[freq[num]]--;
                if (count[freq[num]] == 0) {
                    count.erase(freq[num]);
                }
            }
            freq[num]++;
            count[freq[num]]++;
            maxFreq = max(maxFreq, freq[num]);
            
            // 检查当前前缀是否满足条件
            if (checkValid(freq, count, maxFreq, i + 1)) {
                result = i + 1;
            }
        }
        
        return result;
    }
    
private:
    bool checkValid(unordered_map<int, int>& freq, 
                   unordered_map<int, int>& count,
                   int maxFreq, int length) {
        // 情况1: 所有数字都只出现一次
        if (maxFreq == 1) {
            return true;
        }
        
        // 情况2: 只有一种频率
        if (count.size() == 1) {
            // 要么所有数字都出现1次，要么只有一个数字
            return maxFreq == 1 || count.begin()->second == 1;
        }
        
        // 情况3: 有两种频率
        if (count.size() == 2) {
            auto it1 = count.begin();
            auto it2 = next(it1);
            
            int freq1 = it1->first, cnt1 = it1->second;
            int freq2 = it2->first, cnt2 = it2->second;
            
            // 确保freq1 < freq2
            if (freq1 > freq2) {
                swap(freq1, freq2);
                swap(cnt1, cnt2);
            }
            
            // 情况3a: 一个数字出现1次，其他数字出现相同次数
            if (freq1 == 1 && cnt1 == 1) {
                return true;
            }
            
            // 情况3b: 一个数字出现次数比其他多1，其他数字出现次数相同
            if (freq2 == freq1 + 1 && cnt2 == 1) {
                return true;
            }
        }
        
        return false;
    }
};

// 更简洁的实现版本
class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        unordered_map<int, int> freq, count;
        int maxFreq = 0, res = 0;
        
        for (int i = 0; i < nums.size(); ++i) {
            int num = nums[i];
            
            // 减少旧的频率计数
            if (freq[num] > 0) {
                count[freq[num]]--;
                if (count[freq[num]] == 0) {
                    count.erase(freq[num]);
                }
            }
            
            // 增加新的频率计数
            freq[num]++;
            count[freq[num]]++;
            maxFreq = max(maxFreq, freq[num]);
            
            // 检查是否满足条件
            bool valid = false;
            if (count.size() == 1) {
                // 所有数字频率相同
                auto it = count.begin();
                valid = (it->first == 1) || (it->second == 1);
            } else if (count.size() == 2) {
                auto it1 = count.begin();
                auto it2 = next(it1);
                
                int f1 = it1->first, c1 = it1->second;
                int f2 = it2->first, c2 = it2->second;
                
                if (f1 > f2) {
                    swap(f1, f2);
                    swap(c1, c2);
                }
                
                // 情况1: 一个数字出现1次，其他数字频率相同
                // 情况2: 一个数字频率比其他多1，其他数字频率相同
                valid = (f1 == 1 && c1 == 1) || (f2 == f1 + 1 && c2 == 1);
            }
            
            if (valid) {
                res = i + 1;
            }
        }
        
        return res;
    }
};
