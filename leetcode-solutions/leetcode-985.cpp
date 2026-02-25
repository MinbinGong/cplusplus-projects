/**
 * 985. Sum of Even Numbers After Queries
 *
 * We have an array A of integers, and an array queries of queries.
 *
 * For the i-th query val = queries[i][0], index = queries[i][1], we add val to A[index].  Then, the answer to the i-th query is the sum of the even values of A.
 *
 * (Here, the given index = queries[i][1] is a 0-based index, and each query permanently modifies the array A.)
 *
 * Return the answer to all queries.  Your answer array should have answer[i] as the answer to the i-th query.
 *
 * Example 1:
 *
 * Input: A = [1,2,3,4], queries = [[1,0],[-3,1],[-4,0],[2,3]]
 * Output: [8,6,2,4]
 * Explanation:
 * At the beginning, the array is [1,2,3,4].
 * 
 * Example 2:
 *
 * Input: A = [1], queries = [[4,0]]
 * Output: [0]
 * 
 * Note:
 *
 * 1 <= A.length <= 10000
 * -10000 <= A[i] <= 10000
 * 1 <= queries.length <= 10000
 * -10000 <= queries[i][0] <= 10000
 * 0 <= queries[i][1] < A.length
 */
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
        int evenSum = 0;
        // Compute initial sum of even numbers
        for (int x : A) {
            if (x % 2 == 0) evenSum += x;
        }

        vector<int> result;
        for (auto& q : queries) {
            int val = q[0];
            int idx = q[1];
            int oldVal = A[idx];
            int newVal = oldVal + val;

            // Remove old value from sum if it was even
            if (oldVal % 2 == 0) evenSum -= oldVal;
            // Add new value to sum if it is even
            if (newVal % 2 == 0) evenSum += newVal;

            A[idx] = newVal;                // update the array
            result.push_back(evenSum);       // store answer after this query
        }
        return result;
    }
};