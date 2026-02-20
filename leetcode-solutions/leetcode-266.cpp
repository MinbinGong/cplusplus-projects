/*
 * Palindrome Permutation
 * 
 * Given a string, determine if a permutation of the string could form a palindrome.
 * 
 * Example 1:
 * Input: "code"
 * Output: false
 * 
 * Example 2:
 * Input: "aab"
 * Output: true
 * 
 * Example 3:
 * Input: "carerac"
 * Output: true
 * 
 * Constraints:
 * 1. The string consists of only lowercase English letters.
 * 2. The length of the string will be in the range of [1, 1000].
 */
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution1 {
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> freq;
        for (char c : s) {
            freq[c]++;
        }
        int oddCount = 0;
        for (auto& p : freq) {
            if (p.second % 2 == 1) {
                oddCount++;
                if (oddCount > 1) return false;
            }
        }
        return true;
    }
};

class Solution2 {
public:
    bool canPermutePalindrome(string s) {
        unordered_set<char> oddSet;
        for (char c : s) {
            if (oddSet.count(c)) {
                oddSet.erase(c);
            } else {
                oddSet.insert(c);
            }
        }
        return oddSet.size() <= 1;
    }
};