/**
 * 1395. Count Number of Teams
 * 
 * There are n soldiers standing in a line. Each soldier is assigned a unique rating value.
 * 
 * You have to form a team of 3 soldiers amongst them under the following rules:
 * 
 * Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
 * A team is valid if: (rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k]) where (0 <= i < j < k < n).
 * Return the number of teams you can form given the conditions. (soldiers can be part of multiple teams).
 * 
 * Example 1:
 * Input: rating = [2,5,3,4,1]
 * Output: 3
 * Explanation: We can form three teams given the conditions. (2,3,4), (5,4,1), (5,3,1). 
 * 
 * Example 2:
 * Input: rating = [2,1,3]
 * Output: 0
 * Explanation: There are no teams that can be formed.
 * 
 * Example 3:
 * Input: rating = [1,2,3,4]
 * Output: 4
 * 
 * Note:
 * n == rating.length
 * 3 <= n <= 1000
 * 1 <= rating[i] <= 10^5
 * All the integers in rating are unique.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        int ans = 0;
        // iterate over the middle element j
        for (int j = 1; j < n - 1; ++j) {
            int leftLess = 0, leftGreater = 0;
            int rightLess = 0, rightGreater = 0;
            
            // count elements on the left
            for (int i = 0; i < j; ++i) {
                if (rating[i] < rating[j]) leftLess++;
                else if (rating[i] > rating[j]) leftGreater++;
            }
            // count elements on the right
            for (int k = j + 1; k < n; ++k) {
                if (rating[k] < rating[j]) rightLess++;
                else if (rating[k] > rating[j]) rightGreater++;
            }
            // increasing teams: leftLess * rightGreater
            // decreasing teams: leftGreater * rightLess
            ans += leftLess * rightGreater + leftGreater * rightLess;
        }
        return ans;
    }
};