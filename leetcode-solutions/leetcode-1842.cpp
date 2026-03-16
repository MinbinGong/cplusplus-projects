/**
 * 1842. Next Palindrome Using Same Digits
 * https://leetcode.com/problems/next-palindrome-using-same-digits/
 * 
 * You are given a numeric string num, representing a very large palindrome.
 * 
 * Return the smallest palindrome larger than num that can be created by rearranging its digits. If no such palindrome exists, return an empty string "".
 * 
 * A palindrome is a number that reads the same backward as forward.
 * 
 * Example 1:
 * Input: num = "1221"
 * Output: "2112"
 * Explanation: The next palindrome larger than "1221" is "2112".
 * 
 * Example 2:
 * Input: num = "32123"
 * Output: "33133"
 * Explanation: The next palindrome larger than "32123" is "33133".
 * 
 * Example 3:
 * Input: num = "123"
 * Output: "212"
 * Explanation: The next palindrome larger than "123" is "212".
 * 
 * Constraints:
 * 1 <= num.length <= 105
 * num is a palindrome.
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string nextPalindrome(string num) {
        int n = num.size();
        vector<int> count(10, 0);
        for (char c : num) count[c - '0']++;

        // check if a palindrome can be formed
        int odd = 0, mid = -1;
        for (int d = 0; d < 10; ++d) {
            if (count[d] % 2) {
                odd++;
                mid = d;
            }
        }
        if ((n % 2 == 0 && odd > 0) || (n % 2 == 1 && odd != 1))
            return "";

        int m = n / 2;                     // length of left half
        string left = num.substr(0, m);    // original left half
        string right = num.substr(n - m);  // original right half
        char midChar = (n % 2 == 1) ? num[m] : 0;

        // required counts for the left half
        vector<int> need(10, 0);
        for (int d = 0; d < 10; ++d) need[d] = count[d] / 2;

        // check if original left half already satisfies the counts
        vector<int> leftCnt(10, 0);
        for (char c : left) leftCnt[c - '0']++;
        bool leftValid = true;
        for (int d = 0; d < 10; ++d)
            if (leftCnt[d] != need[d]) leftValid = false;

        // if it does, build the corresponding palindrome and compare
        if (leftValid) {
            string cand;
            if (n % 2 == 0)
                cand = left + string(left.rbegin(), left.rend());
            else
                cand = left + midChar + string(left.rbegin(), left.rend());
            if (cand > num) return cand;
            // otherwise we need the next left half
        }

        // find the next valid left half greater than the original left
        string nextLeft = nextLeftHalf(need, left);
        if (nextLeft.empty()) return "";

        // build the full palindrome
        if (n % 2 == 0)
            return nextLeft + string(nextLeft.rbegin(), nextLeft.rend());
        else
            return nextLeft + char(mid + '0') + string(nextLeft.rbegin(), nextLeft.rend());
    }

private:
    // returns the smallest string (by lexicographic order) composed of the
    // multiset given by 'cnt' that is strictly greater than 'A'.
    // if none exists, returns an empty string.
    string nextLeftHalf(vector<int> cnt, const string& A) {
        int m = A.size();
        vector<int> cur = cnt;
        vector<int> prefix;
        int i;

        // try to match the prefix of A as far as possible
        for (i = 0; i < m; ++i) {
            int d = A[i] - '0';
            if (cur[d] > 0) {
                cur[d]--;
                prefix.push_back(d);
            } else {
                break;
            }
        }

        if (i == m) {
            // A itself is a valid left half -> use next_permutation
            if (next_permutation(prefix.begin(), prefix.end())) {
                string res;
                for (int x : prefix) res += char(x + '0');
                return res;
            }
            return "";
        }

        // at position i we cannot put A[i]; try a larger digit
        int target = A[i] - '0';
        for (int d = target + 1; d <= 9; ++d) {
            if (cur[d] > 0) {
                string res;
                for (int j = 0; j < i; ++j) res += char(prefix[j] + '0');
                res += char(d + '0');
                cur[d]--;
                // fill the rest with the smallest possible digits
                for (int x = 0; x <= 9; ++x) {
                    while (cur[x] > 0) {
                        res += char(x + '0');
                        cur[x]--;
                    }
                }
                return res;
            }
        }

        // need to backtrack
        for (int j = i - 1; j >= 0; --j) {
            int old = prefix[j];
            cur[old]++;                       // put the old digit back
            target = A[j] - '0';
            for (int d = target + 1; d <= 9; ++d) {
                if (cur[d] > 0) {
                    string res;
                    for (int k = 0; k < j; ++k) res += char(prefix[k] + '0');
                    res += char(d + '0');
                    cur[d]--;
                    for (int x = 0; x <= 9; ++x) {
                        while (cur[x] > 0) {
                            res += char(x + '0');
                            cur[x]--;
                        }
                    }
                    return res;
                }
            }
        }
        return "";
    }
};