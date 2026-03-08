/*
 * 1662. Check If Two String Arrays are Equivalent
 *
 * Given two string arrays word1 and word2, return true if the two arrays represent the same string, and false otherwise.
 * A string is represented by an array if the array elements concatenated in order forms the string.
 *
 * Example 1:
 * Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
 * Output: true
 * Explanation:
 * word1 represents string "ab" + "c" -> "abc"
 * word2 represents string "a" + "bc" -> "abc"
 * The strings are the same, so return true.
 * 
 * Example 2:
 * Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
 * Output: false
 * Explanation:
 * word1 represents string "a" + "cb" -> "acb"
 * word2 represents string "ab" + "c" -> "abc"
 * The strings are different, so return false.
 * 
 * Example 3:
 * Input: word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
 * Output: true
 * 
 * Constraints:
 * 1 <= word1.length, word2.length <= 10^3
 * 1 <= word1[i].length, word2[i].length <= 10^3
 * 1 <= sum(word1[i].length), sum(word2[i].length) <= 10^3
 * word1[i] and word2[i] consist of lowercase letters.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution1 {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        string s1, s2;
        for (const string& w : word1) s1 += w;
        for (const string& w : word2) s2 += w;
        return s1 == s2;
    }
};

class Solution2 {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        int i = 0, j = 0;     // 数组索引
        int p = 0, q = 0;     // 字符串内字符索引
        while (i < word1.size() && j < word2.size()) {
            if (word1[i][p] != word2[j][q]) return false;
            p++;
            q++;
            if (p == word1[i].size()) {
                i++;
                p = 0;
            }
            if (q == word2[j].size()) {
                j++;
                q = 0;
            }
        }
        return i == word1.size() && j == word2.size();
    }
};