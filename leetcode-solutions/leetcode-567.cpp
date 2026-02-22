/*
 * Permutation in String
 *
 * Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.
 * 
 * Example:
 * Input:s1 = "ab" s2 = "eidbaooo"
 * Output:True
 * Explanation: s2 contains one permutation of s1 ("ba").
 * 
 * Input:s1= "ab" s2 = "eidboaoo"
 * Output: False
 * 
 * Note:
 * The input strings only contain lower case letters.
 * The length of both given strings is in range [1, 10,000].
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        if (n1 > n2) return false;

        vector<int> count1(26, 0), count2(26, 0);
        for (char c : s1) count1[c - 'a']++;
        for (int i = 0; i < n1; ++i) count2[s2[i] - 'a']++;

        if (count1 == count2) return true;

        for (int i = n1; i < n2; ++i) {
            count2[s2[i] - 'a']++;
            count2[s2[i - n1] - 'a']--;
            if (count1 == count2) return true;
        }
        return false;
    }
};