/*
 * Prefix and Suffix Search
 *
 * Design a special dictionary which has some words and allows you to search the words in it by a prefix and a suffix.
 * 
 * Implement the WordFilter class:
 * 
 * WordFilter(string[] words) Initializes the object with the words in the dictionary.
 * f(string prefix, string suffix) Returns the index of the word in the dictionary which has the prefix prefix and the suffix suffix. If there is more than one valid index, return the largest of them. If there is no such word in the dictionary, return -1.
 * 
 * Note:
 * 1. 1 <= words.length <= 15000
 * 2. 1 <= words[i].length <= 10
 * 3. 1 <= prefix.length, suffix.length <= 10
 * 4. words[i], prefix and suffix consist of lower-case English letters only.
 * 5. At most 15000 calls will be made to the function f.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class WordFilter {
private:
    unordered_map<string, int> dict; // key: prefix#suffix -> max index

public:
    WordFilter(vector<string>& words) {
        int n = words.size();
        for (int idx = 0; idx < n; ++idx) {
            const string& w = words[idx];
            int len = w.size();
            // generate all prefix-suffix combinations
            for (int i = 0; i <= len; ++i) { // prefix length i (0..len)
                string prefix = w.substr(0, i);
                for (int j = 0; j <= len; ++j) { // suffix length j (0..len)
                    string suffix = w.substr(len - j);
                    string key = prefix + "#" + suffix;
                    dict[key] = idx; // later words overwrite earlier ones (higher index)
                }
            }
        }
    }

    int f(string prefix, string suffix) {
        string key = prefix + "#" + suffix;
        auto it = dict.find(key);
        if (it != dict.end()) return it->second;
        return -1;
    }
};