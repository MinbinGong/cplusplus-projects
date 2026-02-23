/*
 * To Lower Case
 *
 * Implement function ToLowerCase() that has a string parameter str, and returns the same string in lowercase.
 * 
 * Example 1:
 *
 * Input: "Hello"
 * Output: "hello"
 * 
 * Example 2:
 *
 * Input: "here"
 * Output: "here"
 * 
 * Example 3:
 *
 * Input: "LOVELY"
 * Output: "lovely"
 * 
 * Note:
 * 1. str will have length in range [1, 100].
 * 2. str will consist only of letters.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string toLowerCase(string s) {
        for (char& c : s) {
            if (c >= 'A' && c <= 'Z') {
                c = c - 'A' + 'a';
            }
        }
        return s;
    }
};