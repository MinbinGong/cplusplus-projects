/*
 * 767. Reorganize String
 *
 * Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.
 * 
 * If possible, output any possible result.  If not possible, return the empty string.
 * 
 * Example 1:
 * Input: S = "aab"
 * Output: "aba"
 * 
 * Example 2:
 * Input: S = "aaab"
 * Output: ""
 * 
 * Note:
 * 1. S will consist of lowercase letters and have length in range [1, 500].
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string reorganizeString(string s) {
        // Count frequency of each character
        unordered_map<char, int> freq;
        for (char c : s) freq[c]++;

        // Max heap: store pairs (frequency, character)
        // We use pair<int, char> and default max-heap on first element
        priority_queue<pair<int, char>> pq;
        for (auto& p : freq) {
            pq.push({p.second, p.first});
        }

        string res;
        while (pq.size() > 1) {
            // Take two most frequent characters
            auto first = pq.top(); pq.pop();
            auto second = pq.top(); pq.pop();

            // Append them to result
            res += first.second;
            res += second.second;

            // Decrease frequencies and push back if still > 0
            if (--first.first > 0) pq.push(first);
            if (--second.first > 0) pq.push(second);
        }

        // If one character left
        if (!pq.empty()) {
            auto last = pq.top(); pq.pop();
            // If its frequency is more than 1, it means it would be adjacent to itself
            // But since we only have one type left and result is built,
            // check if last char is same as previous? Actually if last.freq > 1,
            // then we would have to place it consecutively. But by the condition
            // max frequency <= (n+1)/2, last.freq should be 1 at this point.
            // Still, we should check to be safe.
            if (last.first > 1) return "";
            res += last.second;
        }

        // Final sanity: ensure no two adjacent are same (should hold by construction)
        return res;
    }
};