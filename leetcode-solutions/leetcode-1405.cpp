/**
 * 1405. Longest Happy String
 * 
 * A string s is called happy if it satisfies the following conditions:
 * s only contains the letters 'a', 'b', and 'c'.
 * s does not contain any of "aaa", "bbb", or "ccc" as a substring.
 * s contains at most a occurrences of the letter 'a'.
 * s contains at most b occurrences of the letter 'b'.
 * s contains at most c occurrences of the letter 'c'.
 * Given three integers a, b, and c, return the longest possible happy string. If there are multiple longest happy strings, return any of them. If there is no such string, return the empty string "".
 * A substring is a contiguous sequence of characters within a string.
 * 
 * Example 1:
 * Input: a = 1, b = 1, c = 7
 * Output: "ccaccbcc"
 * Explanation: "ccbccacc" would also be a correct answer.
 * 
 * Example 2:
 * Input: a = 7, b = 1, c = 0
 * Output: "aabaa"
 * Explanation: It is the only correct answer in this case.
 * 
 * Constraints:
 * 0 <= a, b, c <= 100
 * a + b + c > 0
 * 
 */
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <string>
using namespace std;

class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        // Max heap: store pairs of (remaining count, character)
        priority_queue<pair<int, char>> pq;
        if (a > 0) pq.push({a, 'a'});
        if (b > 0) pq.push({b, 'b'});
        if (c > 0) pq.push({c, 'c'});

        string result;
        while (!pq.empty()) {
            auto [count1, ch1] = pq.top();
            pq.pop();

            int n = result.size();
            // Check if using ch1 would create three consecutive identical letters
            if (n >= 2 && result[n - 1] == ch1 && result[n - 2] == ch1) {
                // Cannot use ch1 now, try the next most frequent character
                if (pq.empty()) break;               // No other character available
                auto [count2, ch2] = pq.top();
                pq.pop();

                result.push_back(ch2);
                count2--;
                if (count2 > 0) pq.push({count2, ch2});
                // Put back ch1 (not used this round)
                pq.push({count1, ch1});
            } else {
                // Safe to use ch1
                result.push_back(ch1);
                count1--;
                if (count1 > 0) pq.push({count1, ch1});
            }
        }
        return result;
    }
};