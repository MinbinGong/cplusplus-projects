/*
 * Shortest Word Distance
 *
 * Constraints:
 * 1. 1 <= words.length <= 3 * 10^4
 * 2. 1 <= words[i].length <= 10
 * 3. words[i] consists of lowercase English letters.
 * 4. word1 and word2 are in words.
 * 5. word1 != word2
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int shortestDistance(vector<string>& wordsDict, string word1, string word2) {
        int i1 = -1, i2 = -1;
        int minDist = wordsDict.size(); // initialize with maximum possible
        
        for (int i = 0; i < wordsDict.size(); ++i) {
            if (wordsDict[i] == word1) {
                i1 = i;
                if (i2 != -1) {
                    minDist = min(minDist, abs(i1 - i2));
                }
            } else if (wordsDict[i] == word2) {
                i2 = i;
                if (i1 != -1) {
                    minDist = min(minDist, abs(i1 - i2));
                }
            }
        }
        return minDist;
    }
};