/*
 * 809. Expressive Words
 * 
 * Sometimes people repeat letters to represent extra feeling, such as "hello" -> "heeellooo", "hi" -> "hiiii".  In these strings like "heeellooo", we have groups of adjacent letters that are all the same:  "h", "eee", "ll", "ooo".
 * 
 * For some given string S, a query word is stretchy if it can be made to be equal to S by any number of applications of the following extension operation: choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is 3 or more.
 * 
 * Example:
 * Input: 
 * S = "heeellooo"
 * words = ["hello", "hi", "helo"]
 * Output: 1
 * Explanation: 
 * We can extend "e" and "o" in the word "hello" to get "heeellooo".
 * We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.
 * 
 * Note:
 * 0 <= len(S) <= 100.
 * 0 <= len(words) <= 100.
 * 0 <= len(words[i]) <= 100.
 * S and all words in words consist only of lowercase letters
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int expressiveWords(string S, vector<string>& words) {
        int ans = 0;
        for (const string& w : words) {
            if (check(S, w)) ans++;
        }
        return ans;
    }

private:
    bool check(const string& s, const string& w) {
        int i = 0, j = 0;
        int ns = s.size(), nw = w.size();
        while (i < ns && j < nw) {
            if (s[i] != w[j]) return false;
            char c = s[i];
            int cntS = 0;
            while (i < ns && s[i] == c) { cntS++; i++; }
            int cntW = 0;
            while (j < nw && w[j] == c) { cntW++; j++; }
            if (cntS < cntW) return false;               // S 中数量不够
            if (cntS != cntW && cntS < 3) return false;  // 不能扩展的情况
        }
        return i == ns && j == nw;  // 必须同时结束
    }
};