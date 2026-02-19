/*
 * Longest Substring with At Most Two Distinct Characters
 * 
 * Given a string s, return the length of the longest substring that contains at most two distinct characters.
 * 
 * Constraints:
 * 1. 1 <= s.length <= 105
 * 2. s consists of English letters.
 * 3. s consists of only lowercase English letters.
 * 4. s consists of at most 104 characters.
 */
#include <string>
#include <unordered_map>
using namespace std;

int lengthOfLongestSubstringTwoDistinct(string s) {
    int n = s.size();
    if (n < 3) return n; // Trivial case
    
    unordered_map<char, int> count; // character -> frequency in current window
    int left = 0;
    int maxLen = 0;
    
    for (int right = 0; right < n; ++right) {
        count[s[right]]++;
        
        // Shrink window until we have at most 2 distinct characters
        while (count.size() > 2) {
            char leftChar = s[left];
            count[leftChar]--;
            if (count[leftChar] == 0) {
                count.erase(leftChar);
            }
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}
