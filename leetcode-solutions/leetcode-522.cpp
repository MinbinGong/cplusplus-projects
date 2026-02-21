/*
 * Longest Uncommon Subsequence II
 *
 * Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
 * 
 * An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
 * 
 * A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
 * 
 * For example, "abc" is a subsequence of "aebdc" because you can delete the underlined characters in "aebdc" to get "abc". Other subsequences of "aebdc" include "aebdc", "aeb", and "" (empty string).
 * 
 * Constraints:
 * 2 <= strs.length <= 50
 * 1 <= strs[i].length <= 10
 * strs[i] consists of lowercase English letters.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        int n = strs.size();
        int ans = -1;
        
        for (int i = 0; i < n; ++i) {
            bool isUncommon = true;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (isSubsequence(strs[i], strs[j])) {
                    isUncommon = false;
                    break;
                }
            }
            if (isUncommon) {
                ans = max(ans, (int)strs[i].size());
            }
        }
        return ans;
    }
    
private:
    // Check if s is a subsequence of t
    bool isSubsequence(const string& s, const string& t) {
        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) ++i;
            ++j;
        }
        return i == s.size();
    }
};