/**
 * 1415. The k-th Lexicographical String of All Happy Strings of Length n
 * 
 * A happy string is a string that:
 * consists only of letters of the set ['a', 'b', 'c'].
 * s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
 * For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.
 * Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.
 * Return the kth string of this list or return an empty string if there are less than k happy strings of length n.
 * 
 * Example 1:
 * Input: n = 1, k = 3
 * Output: "c"
 * Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
 * 
 * Example 2:
 * Input: n = 1, k = 4
 * Output: ""
 * Explanation: There are only 3 happy strings of length 1.
 * 
 * Example 3:
 * Input: n = 3, k = 9
 * Output: "cab"
 * Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"].
 * You will find the 9th string = "cab"
 * 
 * Note:
 * 1 <= n <= 10
 * 1 <= k <= 100
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string getHappyString(int n, int k) {
        int total = 3 * (1 << (n - 1)); // total number of happy strings
        if (k > total) return "";
        
        string res;
        for (int i = 0; i < n; ++i) {
            for (char c : {'a', 'b', 'c'}) {
                if (!res.empty() && c == res.back()) continue; // cannot repeat previous char
                int remaining = n - i - 1; // positions left after picking c
                int cnt = 1 << remaining;  // number of strings with this prefix
                if (k > cnt) {
                    k -= cnt;               // skip this whole block
                } else {
                    res.push_back(c);       // take this character
                    break;
                }
            }
        }
        return res;
    }
};