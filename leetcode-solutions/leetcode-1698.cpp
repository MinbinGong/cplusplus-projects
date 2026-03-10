/*
 * 1698. Number of Distinct Substrings in a String
 * 
 * Given a string s, return the number of distinct substrings of s.
 * 
 * A substring of a string is obtained by deleting any number of characters (possibly zero) from the front of the string and any number of characters (possibly zero) from the back of the string.
 * 
 * Example 1:
 * Input: s = "aabbaba"
 * Output: 21
 * Explanation: The set of distinct substrings is ["a","b","aa","bb","ab","ba","aab","abb","bba","aba","aabb","abba","bbab","baba","aabba","abbab","bbaba","aabbab","abbaba"].
 * 
 * Example 2:
 * Input: s = "abcdefg"
 * Output: 28
 * 
 * Constraints:
 * 1 <= s.length <= 500
 * s consists of lowercase English letters.
 * 
 * Follow up: Can you solve this problem in O(n) time complexity?
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int countDistinct(string s) {
        int n = s.size();
        int count = 0;
        vector<vector<int>> trie(1, vector<int>(26, 0));
        
        for (int i = 0; i < n; ++i) {
            int node = 0;
            
            for (int j = i; j < n; ++j) {
                int idx = s[j] - 'a';
                
                if (trie[node][idx] == 0) {
                    trie[node][idx] = trie.size();
                    trie.push_back(vector<int>(26, 0));
                    count++;
                }
                
                node = trie[node][idx];
            }
        }
        
        return count;
    }
};