/*
 * 1014. Best Sightseeing Pair
 *
 * Given an array A of positive integers, A[i] represents the value of the i-th sightseeing spot, and two sightseeing spots i and j have distance j - i between them.
 * 
 * The score of a pair (i < j) of sightseeing spots is (A[i] + A[j] + i - j) : the sum of the values of the sightseeing spots, minus the distance between them.
 * 
 * Return the maximum score of a pair of sightseeing spots.
 * 
 * Example 1:
 *
 * Input: [8,1,5,2,6]
 * Output: 11
 * Explanation: i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11
 * 
 * Note:
 *
 * 2 <= A.length <= 50000
 * 1 <= A[i] <= 1000
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        int maxScore = 0;
        int maxI = A[0] + 0; // best A[i] + i encountered so far
        for (int j = 1; j < A.size(); ++j) {
            // evaluate pair (i, j) using best previous i
            maxScore = max(maxScore, maxI + A[j] - j);
            // update best i for future j's
            maxI = max(maxI, A[j] + j);
        }
        return maxScore;
    }
};