/*
 * 1170. Compare Strings by Frequency of the Smallest Character
 * 
 * Let's define a function f(s) over a non-empty string s, which calculates the frequency of the smallest character in s. For example, if s = "dcce" then f(s) = 2 because the smallest character is "c" and its frequency is 2.
 * 
 * Now, given string arrays queries and words, return an integer array answer, where each answer[i] is the number of words such that f(queries[i]) < f(W), where W is a word in words.
 * 
 * Example 1:
 * Input: queries = ["cbd"], words = ["zaaaz"]
 * Output: [1]
 * Explanation: On the first query we have f("cbd") = 1, f("zaaaz") = 3 so f("cbd") < f("zaaaz").
 * 
 * Example 2:
 * Input: queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
 * Output: [1,2]
 * 
 * Note:
 * 1 <= queries.length <= 2000
 * 1 <= words.length <= 2000
 * 1 <= queries[i].length, words[i].length <= 10
 * queries[i][j], words[i][j] are English lowercase letters.
 */
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        // Step 1: compute f(word) for each word and sort
        vector<int> fwords;
        for (const string& w : words) {
            fwords.push_back(calcF(w));
        }
        sort(fwords.begin(), fwords.end());

        // Step 2: for each query, binary search how many fwords are > f(query)
        vector<int> result;
        for (const string& q : queries) {
            int fq = calcF(q);
            // first element > fq
            auto it = upper_bound(fwords.begin(), fwords.end(), fq);
            result.push_back(fwords.end() - it);
        }
        return result;
    }

private:
    int calcF(const string& s) {
        char smallest = 'z';
        for (char c : s) {
            if (c < smallest) smallest = c;
        }
        int count = 0;
        for (char c : s) {
            if (c == smallest) ++count;
        }
        return count;
    }
};