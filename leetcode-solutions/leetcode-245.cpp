/*
 * Shortest Word Distance III
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
    int shortestWordDistance(vector<string>& wordsDict, string word1, string word2) {
        int n = wordsDict.size();
        int minDist = n; // initialize with maximum possible distance
        
        if (word1 == word2) {
            // Case: same word – find minimum distance between two occurrences
            int prev = -1;
            for (int i = 0; i < n; ++i) {
                if (wordsDict[i] == word1) {
                    if (prev != -1) {
                        minDist = min(minDist, i - prev);
                    }
                    prev = i;
                }
            }
        } else {
            // Case: different words – standard two‑pointer approach
            int p1 = -1, p2 = -1;
            for (int i = 0; i < n; ++i) {
                if (wordsDict[i] == word1) {
                    p1 = i;
                }
                if (wordsDict[i] == word2) {
                    p2 = i;
                }
                if (p1 != -1 && p2 != -1) {
                    minDist = min(minDist, abs(p1 - p2));
                }
            }
        }
        
        return minDist;
    }
};