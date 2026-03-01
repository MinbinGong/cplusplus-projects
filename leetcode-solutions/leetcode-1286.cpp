/**
 * 1286. Iterator for Combination
 * 
 * Design the CombinationIterator class:
 * 
 * CombinationIterator(string characters, int combinationLength) Initializes the object with a string characters of sorted
 * distinct lowercase English letters and a number combinationLength as arguments.
 * 
 * next() Returns the next combination of length combinationLength in lexicographical order.
 * 
 * hasNext() Returns true if and only if there exists a next combination.
 * 
 * Example 1:
 * Input
 * ["CombinationIterator", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
 * [["abc", 2], [], [], [], [], [], []]
 * Output
 * [null, "ab", true, "ac", true, "bc", false]
 * 
 * Explanation
 * CombinationIterator itr = new CombinationIterator("abc", 2);
 * itr.next();    // return "ab"
 * itr.hasNext(); // return True
 * itr.next();    // return "ac"
 * itr.hasNext(); // return True
 * itr.next();    // return "bc"
 * itr.hasNext(); // return False
 * 
 * Note:
 * 1 <= combinationLength <= characters.length <= 15
 * All the characters of characters are unique.
 * At most 104 calls will be made to next and hasNext.
 * It's guaranteed that all calls of the function next are valid.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class CombinationIterator {
private:
    string chars;               // original characters string
    int k;                       // length of each combination
    vector<int> indices;         // current combination indices
    bool hasNextComb;            // whether there is a next combination

public:
    CombinationIterator(string characters, int combinationLength) {
        chars = characters;
        k = combinationLength;
        // Initialize indices to the first combination: [0, 1, ..., k-1]
        indices.resize(k);
        for (int i = 0; i < k; ++i) {
            indices[i] = i;
        }
        hasNextComb = (k <= chars.size());
    }
    
    string next() {
        // Build the current combination from the indices
        string current;
        for (int idx : indices) {
            current.push_back(chars[idx]);
        }
        
        // Update indices to the next combination
        int n = chars.size();
        int i = k - 1;
        // Find the rightmost index that can be incremented
        while (i >= 0 && indices[i] == n - k + i) {
            --i;
        }
        if (i >= 0) {
            ++indices[i];
            for (int j = i + 1; j < k; ++j) {
                indices[j] = indices[j - 1] + 1;
            }
        } else {
            // No more combinations
            hasNextComb = false;
        }
        
        return current;
    }
    
    bool hasNext() {
        return hasNextComb;
    }
};
