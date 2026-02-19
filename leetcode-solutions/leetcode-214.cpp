/*
 * Shortest Palindrome
 * 
 * Given a string s, you can convert it to a palindrome by adding characters in front of it. Find and return the
 * shortest palindrome you can find by performing this transformation.
 * 
 * Constraints:
 * 1. 0 <= s.length <= 5 * 104
 * 2. s consists of lowercase English letters only.
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        if (n == 0) return s;
        
        string rev = s;
        reverse(rev.begin(), rev.end());
        
        // Build combined string: s + '#' + rev
        string t = s + "#" + rev;
        int m = t.size();
        vector<int> pi(m, 0);
        
        // Compute KMP prefix function
        for (int i = 1; i < m; ++i) {
            int j = pi[i - 1];
            while (j > 0 && t[i] != t[j]) {
                j = pi[j - 1];
            }
            if (t[i] == t[j]) {
                ++j;
            }
            pi[i] = j;
        }
        
        int len = pi.back(); // length of longest palindrome prefix
        string add = rev.substr(0, n - len); // characters to prepend
        return add + s;
    }
};