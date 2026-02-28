/**
 * 1209. Remove All Adjacent Duplicates in String II
 *
 * You are given a string s and an integer k, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them, causing the left and the right side of the deleted substring to concatenate together.
 *
 * We repeatedly make k duplicate removals on s until we no longer can.
 *
 * Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.
 *
 *
 *
 * Example 1:
 *
 * Input: s = "abcd", k = 2
 * Output: "abcd"
 * Explanation: There's nothing to delete.
 *
 * Example 2:
 *
 * Input: s = "deeedbbcccbdaa", k = 3
 * Output: "aa"
 * Explanation:
 * First delete "eee" and "ccc", get "ddbbbdaa"
 * Then delete "bbb", get "dddaa"
 * Finally delete "ddd", get "aa"
 *
 * Example 3:
 *
 * Input: s = "pbbcggttciiippooaais", k = 2
 * Output: "ps"
 *
 *
 * Note:
 *
 * 1 <= s.length <= 10^5
 * 2 <= k <= 10^4
 * s only contains lower case English letters.
 *
 */
#include <string>
#include <stack>

class Solution {
public:
    std::string removeDuplicates(std::string s, int k) {
        std::stack<std::pair<char, int>> st;
        
        for (char c : s) {
            if (!st.empty() && st.top().first == c) {
                st.top().second++;
            } else {
                st.push({c, 1});
            }
            
            if (st.top().second == k) {
                st.pop();
            }
        }
        
        std::string result;
        while (!st.empty()) {
            auto [ch, count] = st.top();
            st.pop();
            result = std::string(count, ch) + result;
        }
        
        return result;
    }
};