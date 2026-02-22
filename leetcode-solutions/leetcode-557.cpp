/*
 * Reverse Words in a String III
 *
 * Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.
 * 
 * Example:
 * Input: "Let's take LeetCode contest"
 * Output: "s'teL ekat edoCteeL tsetnoc"
 * 
 * Note:
 * In the string, each word is separated by single space and there will not be any extra space in the string.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        int i = 0;
        while (i < n) {
            // Find the start of a word
            while (i < n && s[i] == ' ') i++;
            int j = i;
            // Find the end of the word
            while (j < n && s[j] != ' ') j++;
            // Reverse the word from i to j-1
            reverse(s.begin() + i, s.begin() + j);
            i = j;
        }
        return s;
    }
};