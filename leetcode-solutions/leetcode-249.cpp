/*
 * Group Shifted Strings
 * 
 * We can shift a string by shifting each of its letters to its successive letter.
 * 
 * For example, "abc" can be shifted to be "bcd".
 * 
 * We can keep shifting the string to form a sequence.
 * 
 * For example, we can keep shifting "abc" to form the sequence: "abc" -> "bcd" -> ... -> "xyz".
 * 
 * Given an array of strings strings, group all strings[i] that belong to the same shifting sequence. You may return the
 * answer in any order.
 * 
 * Constraints:
 * 1. 1 <= strings.length <= 200
 * 2. 1 <= strings[i].length <= 50
 * 3. strings[i] consists of lowercase English letters.
 */
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> groups;
        
        for (const string& s : strings) {
            string key;
            if (s.length() == 1) {
                key = ""; // all single characters belong together
            } else {
                char base = s[0];
                for (size_t i = 1; i < s.length(); ++i) {
                    int diff = (s[i] - base + 26) % 26;
                    key += to_string(diff) + ",";
                }
            }
            groups[key].push_back(s);
        }
        
        vector<vector<string>> result;
        for (auto& p : groups) {
            result.push_back(p.second);
        }
        return result;
    }
};