/*
 * 1647. Minimum Deletions to Make Character Frequencies Unique
 *
 * A string s is called good if there are no two different characters in s that have the same frequency.
 * Given a string s, return the minimum number of characters you need to delete to make s good.
 * The frequency of a character in a string is the number of times it appears in the string. For example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.
 * 
 * Example 1:
 * Input: s = "aab"
 * Output: 0
 * Explanation: s is already good.
 * 
 * Example 2:
 * Input: s = "aaabbbcc"
 * Output: 2
 * Explanation: You can delete two 'b's resulting in the good string "aaabcc".
 * Another way it to delete one 'b' and one 'c' resulting in the good string "aaabbc".
 * 
 * Example 3:
 * Input: s = "ceabaacb"
 * Output: 2
 * Explanation: You can delete both 'c's resulting in the good string "eabaab".
 * Note that we only care about characters that are still in the string at the end (i.e. frequency of 0 is ignored).
 * 
 * Constraints:
 * 1 <= s.length <= 105
 * s contains only lowercase English letters.
 * 
 */
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int minDeletions(string s) {
        // Count frequencies of each character (a-z)
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        unordered_set<int> used;      // keep track of frequencies already used
        int deletions = 0;
        
        for (int f : freq) {
            int current = f;
            // If current frequency is already used, reduce it until we find an unused one
            while (current > 0 && used.count(current)) {
                current--;
                deletions++;
            }
            // If we got a non-zero new frequency, mark it as used
            if (current > 0) {
                used.insert(current);
            }
            // If current becomes 0, we don't mark it (0 is not considered "used")
        }
        
        return deletions;
    }
};