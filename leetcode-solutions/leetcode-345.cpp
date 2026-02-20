/*
 * Reverse Vowels of a String
 * Write a function that takes a string as input and reverse only the vowels of a string.
 * 
 * Example 1:
 * Input: s = "hello"
 * Output: "holle"
 * 
 * Example 2:
 * Input: s = "leetcode"
 * Output: "leotcede"
 * 
 * Example 3:
 * Input: s = "aA"
 * Output: "Aa"
 * 
 */
#include <string>
#include <cctype>  // for tolower

using namespace std;

class Solution {
public:
    string reverseVowels(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            // Move left pointer until it points to a vowel
            while (left < right && !isVowel(s[left])) {
                ++left;
            }
            // Move right pointer until it points to a vowel
            while (left < right && !isVowel(s[right])) {
                --right;
            }
            // Swap the vowels
            if (left < right) {
                swap(s[left], s[right]);
                ++left;
                --right;
            }
        }
        return s;
    }

private:
    bool isVowel(char c) {
        c = tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};