/*
 * Shortest Word Distance II
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
#include <unordered_map>
using namespace std;

class WordDistance {
private:
    unordered_map<string, vector<int>> posMap; // word -> list of indices (sorted)

public:
    WordDistance(vector<string>& words) {
        for (int i = 0; i < words.size(); ++i) {
            posMap[words[i]].push_back(i);
        }
    }
    
    int shortest(string word1, string word2) {
        const vector<int>& list1 = posMap[word1];
        const vector<int>& list2 = posMap[word2];
        int i = 0, j = 0;
        int minDist = INT_MAX;
        
        // Two‑pointer merge: both lists are sorted
        while (i < list1.size() && j < list2.size()) {
            int dist = abs(list1[i] - list2[j]);
            minDist = min(minDist, dist);
            
            // Move the pointer pointing to the smaller index
            if (list1[i] < list2[j]) {
                ++i;
            } else {
                ++j;
            }
        }
        return minDist;
    }
};