/*
 * 760. Find Anagram Mappings
 *
 * Given two lists Aand B, and B is an anagram of A. B is an anagram of A means B is made by randomizing the order of the elements in A.
 * 
 * We want to find an index mapping P, from A to B. A mapping P[i] = j means the ith element in A appears in B at index j.
 * 
 * These lists A and B may contain duplicates. If there are multiple answers, output any of them.
 * 
 * For example, given
 * 
 * A = [12, 28, 46, 32, 50]
 * B = [50, 12, 32, 46, 28]
 * We should return
 * [1, 4, 3, 2, 0]
 * as P[0] = 1 because the 0th element of A appears at B[1], and P[1] = 4 because the 1st element of A appears at B[4], and so on.
 * 
 * Note:
 * 1. A, B have equal lengths in range [1, 100].
 * 2. A[i], B[i] are integers in range [0, 10^5].
 * 
 */
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> anagramMappings(vector<int>& A, vector<int>& B) {
        // Map each value to a queue of indices in B where it occurs
        unordered_map<int, queue<int>> posMap;
        for (int i = 0; i < B.size(); ++i) {
            posMap[B[i]].push(i);
        }

        vector<int> result;
        for (int val : A) {
            int idx = posMap[val].front();   // get the first occurrence
            posMap[val].pop();                // remove it so it's not reused
            result.push_back(idx);
        }
        return result;
    }
};