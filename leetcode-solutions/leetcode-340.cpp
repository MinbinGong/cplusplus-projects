/*
 * Longest Substring with At Most K Distinct Characters
 *
 * Given a string s and an integer k, return the length of the longest substring of s that contains at most k distinct characters.
 * 
 * Example 1:
 * Input: s = "eceba", k = 2
 * Output: 3
 * Explanation: The substring is "ece" with length 3.
 * 
 * Example 2:
 * Input: s = "aa", k = 1
 * Output: 2
 * Explanation: The substring is "aa" with length 2.
 * 
 * Example 3:
 * Input: s = "aabbcc", k = 2
 * Output: 4
 * Explanation: The substring is "aabb" with length 4.
 * 
 */
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0 || s.empty()) return 0;
        
        unordered_map<char, int> count; // character -> frequency in current window
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.size(); ++right) {
            // expand window by adding s[right]
            count[s[right]]++;
            
            // if distinct characters exceed k, shrink from left
            while (count.size() > k) {
                char leftChar = s[left];
                count[leftChar]--;
                if (count[leftChar] == 0) {
                    count.erase(leftChar);
                }
                left++;
            }
            
            // update maximum length
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};