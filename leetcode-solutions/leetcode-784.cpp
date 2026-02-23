/*
 * 784. Letter Case Permutation
 *
 * Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.
 * 
 * Return a list of all possible strings we could create. You can return the output in any order.
 * 
 * Example 1:
 * Input: S = "a1b2"
 * Output: ["a1b2","a1B2","A1b2","A1B2"]
 * 
 * Example 2:
 * Input: S = "3z4"
 * Output: ["3z4","3Z4"]
 * 
 * Example 3:
 * Input: S = "12345"
 * Output: ["12345"]
 * 
 * Example 4:
 * Input: S = "0"
 * Output: ["0"]
 * 
 * Note:
 * 1. S will be a string with length between 1 and 12.
 * 2. S will consist only of letters or digits.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> result;
        string current;
        backtrack(s, 0, current, result);
        return result;
    }

private:
    void backtrack(const string& s, int idx, string& current, vector<string>& result) {
        if (idx == s.length()) {
            result.push_back(current);
            return;
        }

        char c = s[idx];
        if (isalpha(c)) {
            // try lowercase
            current.push_back(tolower(c));
            backtrack(s, idx + 1, current, result);
            current.pop_back();

            // try uppercase
            current.push_back(toupper(c));
            backtrack(s, idx + 1, current, result);
            current.pop_back();
        } else {
            // digit – just append
            current.push_back(c);
            backtrack(s, idx + 1, current, result);
            current.pop_back();
        }
    }
};