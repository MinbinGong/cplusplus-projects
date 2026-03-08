/*
 * 1668. Maximum Repeating Substring
 * 
 * For a string sequence, a string word is k-repeating if word concatenated k times is a substring of sequence. The word's maximum k-repeating value is the highest value k where word is k-repeating in sequence. If word is not a substring of sequence, word's maximum k-repeating value is 0.
 * 
 * Given strings sequence and word, return the maximum k-repeating value of word in sequence.
 * 
 * Example 1:
 * Input: sequence = "ababc", word = "ab"
 * Output: 2
 * Explanation: "abab" is a substring in "ababc".
 * 
 * Example 2:
 * Input: sequence = "ababc", word = "ba"
 * Output: 1
 * Explanation: "ba" is a substring in "ababc". "baba" is not a substring in "ababc".
 * 
 * Example 3:
 * Input: sequence = "ababc", word = "ac"
 * Output: 0
 * Explanation: "ac" is not a substring in "ababc". 
 * 
 * Constraints:
 * 1 <= sequence.length <= 100
 * 1 <= word.length <= 100
 * sequence and word contains only lowercase English letters.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution1 {
public:
    int maxRepeating(string sequence, string word) {
        int n = sequence.size();
        int ans = 0;
        string cur = word;
        while (cur.size() <= n) {
            if (sequence.find(cur) != string::npos) {
                ++ans;
                cur += word;           // 重复次数+1
            } else {
                break;
            }
        }
        return ans;
    }
};

class Solution2 {
public:
    int maxRepeating(string sequence, string word) {
        int n = sequence.size(), m = word.size();
        vector<int> dp(n, 0);           // dp[i] 表示以 i 结尾的连续重复次数
        int ans = 0;
        for (int i = m - 1; i < n; ++i) {
            if (sequence.substr(i - m + 1, m) == word) {
                dp[i] = (i >= m ? dp[i - m] : 0) + 1;
                ans = max(ans, dp[i]);
            }
        }
        return ans;
    }
};