/*
 * 1189. Maximum Number of Balloons
 * 
 * Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.
 * 
 * You can use each character in text at most once. Return the maximum number of instances that can be formed.
 * 
 * Example 1:
 * Input: text = "nlaebolko"
 * Output: 1
 * 
 * Example 2:
 * Input: text = "loonbalxballpoon"
 * Output: 2
 * 
 * Example 3:
 * Input: text = "leetcode"
 * Output: 0
 * 
 * Note:
 * 1 <= text.length <= 10^4
 * text consists of lower case English letters only.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int maxNumberOfBalloons(string text) {
        int cnt[26] = {0};
        for (char c : text) {
            cnt[c - 'a']++;
        }
        // balloon needs: b, a, l/2, o/2, n
        int b = cnt['b' - 'a'];
        int a = cnt['a' - 'a'];
        int l = cnt['l' - 'a'] / 2;
        int o = cnt['o' - 'a'] / 2;
        int n = cnt['n' - 'a'];
        return min({b, a, l, o, n});
    }
};