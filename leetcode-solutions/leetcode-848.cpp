/*
 * 848. Shifting Letters
 * 
 * We have a string S of lowercase letters, and an integer array shifts.
 * 
 * Call the shift of a letter, the next letter in the alphabet, (wrapping around so that 'z' becomes 'a').
 * 
 * For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.
 * 
 * Now for each shifts[i] = x, we want to shift the first i+1 letters of S, x times.
 * 
 * Return the final string after all such shifts to S are applied.
 * 
 * Example 1:
 * Input: S = "abc", shifts = [3,5,9]
 * Output: "rpl"
 * Explanation: 
 * We start with "abc".
 * After shifting the first 1 letters of S by 3, we have "dbc".
 * After shifting the first 2 letters of S by 5, we have "igc".
 * After shifting the first 3 letters of S by 9, we have "rpl", the answer.
 * 
 * Example 2:
 * Input: S = "aaa", shifts = [1,2,3]
 * Output: "gfd"
 * Explanation: 
 * We start with "aaa".
 * After shifting the first 1 letters of S by 1, we have "baa".
 * After shifting the first 2 letters of S by 2, we have "ccz".
 * After shifting the first 3 letters of S by 3, we have "gfd", the answer.
 * 
 * Note:
 * 1 <= S.length = shifts.length <= 20000
 * 0 <= shifts[i] <= 10 ^ 9
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
        long long sum = 0; // 后缀和，注意可能溢出，用 long long
        for (int i = s.size() - 1; i >= 0; --i) {
            sum += shifts[i];
            int shift = sum % 26; // 取模，避免过大
            s[i] = 'a' + (s[i] - 'a' + shift) % 26;
        }
        return s;
    }
};