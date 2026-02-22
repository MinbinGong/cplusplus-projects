/*
 * Find the Closest Palindrome
 *
 * Given an integer n, find the closest integer (not including itself), which is a palindrome.
 * 
 * The 'closest' is defined as absolute difference minimized between two integers.
 * 
 * Example:
 * Input: "123"
 * Output: "121"
 * 
 * Note:
 * The input n is a positive integer represented by string, whose length will not exceed 18.
 * If there is a tie, return the smaller one as answer.
 * 
 */
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
    long long pow10(int k) {
        long long res = 1;
        for (int i = 0; i < k; ++i) res *= 10;
        return res;
    }

    long long makePalindrome(long long half, int len) {
        string halfStr = to_string(half);
        string pal = halfStr;
        if (len % 2 == 0) {
            string rev = halfStr;
            reverse(rev.begin(), rev.end());
            pal += rev;
        } else {
            string rev = halfStr.substr(0, halfStr.size() - 1);
            reverse(rev.begin(), rev.end());
            pal += rev;
        }
        return stoll(pal);
    }

public:
    string nearestPalindromic(string n) {
        int len = n.size();
        long long num = stoll(n);
        set<long long> candidates;
        int halfLen = (len + 1) / 2;
        long long prefix = stoll(n.substr(0, halfLen));

        // Same length candidates
        candidates.insert(makePalindrome(prefix, len));

        long long p2 = prefix + 1;
        if (to_string(p2).size() == halfLen)
            candidates.insert(makePalindrome(p2, len));

        long long p3 = prefix - 1;
        if (p3 >= 0) {
            if (halfLen == 1 || p3 >= pow10(halfLen - 1))
                candidates.insert(makePalindrome(p3, len));
        }

        // Shorter and longer length candidates
        if (len > 1)
            candidates.insert(pow10(len - 1) - 1);   // 999...9
        candidates.insert(pow10(len) + 1);           // 100...001

        // Remove the original number if it appears
        candidates.erase(num);

        // Find the closest
        long long best = -1;
        long long minDiff = LLONG_MAX;
        for (long long cand : candidates) {
            long long diff = llabs(cand - num);
            if (diff < minDiff || (diff == minDiff && cand < best)) {
                minDiff = diff;
                best = cand;
            }
        }
        return to_string(best);
    }
};