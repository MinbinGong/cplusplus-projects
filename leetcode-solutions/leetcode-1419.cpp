/**
 * 1419. Minimum Number of Frogs Croaking
 * 
 * Given the string croakOfFrogs, which represents a combination of the string "croak" from different frogs, that is, multiple frogs can croak at the same time, so multiple “croak” are mixed. Return the minimum number of different frogs to finish all the croak in the given string.
 * 
 * A valid "croak" means a frog is printing 5 letters ‘c’, ’r’, ’o’, ’a’, ’k’ sequentially. The frogs have to print all five letters to finish a croak. If the given string is not a combination of valid "croak" return -1.
 * 
 * Example 1:
 * 
 * Input: croakOfFrogs = "croakcroak"
 * Output: 1 
 * Explanation: One frog yelling "croak" twice.
 * 
 * Example 2:
 * 
 * Input: croakOfFrogs = "crcoakroak"
 * Output: 2 
 * Explanation: The minimum number of frogs is two. 
 * The first frog could yell "crcoakroak".
 * The second frog could yell later "croakcroak".
 * 
 * Example 3:
 * 
 * Input: croakOfFrogs = "croakcrook"
 * Output: -1
 * Explanation: The given string is an invalid combination of "croak" from different frogs.
 * 
 * Example 4:
 * 
 * Input: croakOfFrogs = "croakcroa"
 * Output: -1
 * 
 * Note:
 * 1 <= croakOfFrogs.length <= 10^5
 * All characters in the string are: 'c', 'r', 'o', 'a' or 'k'.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        // counts for ongoing stages: 0:c, 1:r, 2:o, 3:a
        int cnt[4] = {0};
        int maxFrogs = 0;

        for (char ch : croakOfFrogs) {
            if (ch == 'c') {
                cnt[0]++;
            } else if (ch == 'r') {
                if (cnt[0] == 0) return -1;
                cnt[0]--;
                cnt[1]++;
            } else if (ch == 'o') {
                if (cnt[1] == 0) return -1;
                cnt[1]--;
                cnt[2]++;
            } else if (ch == 'a') {
                if (cnt[2] == 0) return -1;
                cnt[2]--;
                cnt[3]++;
            } else if (ch == 'k') {
                if (cnt[3] == 0) return -1;
                cnt[3]--;
                // frog finishes, no increment
            } else {
                // invalid character (should not happen per problem statement)
                return -1;
            }

            int total = cnt[0] + cnt[1] + cnt[2] + cnt[3];
            maxFrogs = max(maxFrogs, total);
        }

        // all frogs must have finished croaking
        if (cnt[0] != 0 || cnt[1] != 0 || cnt[2] != 0 || cnt[3] != 0)
            return -1;

        return maxFrogs;
    }
};