/**
 * 1772. Sort Features by Popularity
 * 
 * You are given a string array features where features[i] is a single word that represents the name of a feature of the latest product you are working on. You have made a survey where users have reported which features they like. You are given a string array responses, where each responses[i] is a string containing space-separated words.
 * 
 * The popularity of a feature is the number of responses[i] that contain the feature. You want to sort the features in non-increasing order by their popularity. If two features have the same popularity, order them by their original index in features. Notice that one response could contain the same feature multiple times; this feature is only counted once in its popularity.
 * 
 * Return the features in sorted order.
 * 
 * Example 1:
 * 
 * Input: features = ["cooler","lock","touch"], responses = ["i like cooler cooler","lock touch cool","locker like touch"]
 * Output: ["touch","cooler","lock"]
 * Explanation: 
 * - "touch" has a popularity of 1.
 * - "cooler" has a popularity of 1.
 * - "lock" has a popularity of 2.
 * 
 * Example 2:
 * 
 * Input: features = ["a","aa","b","c"], responses = ["a","a aa","a a a a a","b a"]
 * Output: ["a","aa","b","c"]
 * 
 * Constraints:
 * 
 * 1 <= features.length <= 104
 * 1 <= features[i].length <= 10
 * features[i] consists of lowercase English letters.
 * All the strings in features are unique.
 * 1 <= responses.length <= 102
 * 1 <= responses[i].length <= 103
 * responses[i] consists of lowercase English letters and spaces.
 * responses[i] does not have leading or trailing spaces.
 * All the words in responses[i] are separated by a single space.
 * 
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> sortFeatures(vector<string>& features, vector<string>& responses) {
        unordered_set<string> featureSet(features.begin(), features.end());
        unordered_map<string, int> freqMap;
        for (const string& f : features) {
            freqMap[f] = 0;
        }
        
        for (const string& resp : responses) {
            istringstream iss(resp);
            string word;
            unordered_set<string> seenWords;
            while (iss >> word) {
                if (featureSet.find(word) != featureSet.end()) {
                    seenWords.insert(word);
                }
            }
            for (const string& w : seenWords) {
                freqMap[w]++;
            }
        }
        
        sort(features.begin(), features.end(), [&](const string& a, const string& b) {
            if (freqMap[a] != freqMap[b]) {
                return freqMap[a] > freqMap[b];
            }
            return a < b;
        });
        
        return features;
    }
};