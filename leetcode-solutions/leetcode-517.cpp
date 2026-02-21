/*
 * Super Washing Machines
 *
 * You have n super washing machines on a line. Initially, each washing machine has some dresses or is empty.
 * 
 * For each move, you could choose any m (1 <= m <= n) washing machines, and pass one dress of each washing machine to one of its adjacent washing machines at the same time.
 * 
 * Given an integer array machines representing the number of dresses in each washing machine from left to right on the line, return the minimum number of moves to make all the washing machines have the same number of dresses. If it is not possible to do it, return -1.
 * 
 * Constraints:
 * n == machines.length
 * 1 <= n <= 104
 * 0 <= machines[i] <= 105
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int total = accumulate(machines.begin(), machines.end(), 0);
        int n = machines.size();

        // If total clothes can't be evenly distributed, it's impossible
        if (total % n != 0) {
            return -1;
        }

        int avg = total / n;
        int ans = 0;
        int balance = 0; // Cumulative imbalance (clothes that need to pass through current point)

        for (int clothes : machines) {
            int diff = clothes - avg; // How many clothes this machine needs (-) or has extra (+)
            balance += diff; // Update the flow passing through this point
            
            // The answer is the maximum of:
            // 1. The current cumulative flow (abs(balance)) - must pass through here.
            // 2. The surplus at this machine (diff) - must be given out one by one.
            ans = max({ans, abs(balance), diff});
        }
        
        return ans;
    }
};