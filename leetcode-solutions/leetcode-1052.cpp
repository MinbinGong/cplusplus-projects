/*
 * 1052. Grumpy Bookstore Owner
 *
 * Today, the bookstore owner has a store open for customers.length minutes.  Every minute, some number of customers (customers[i]) enter the store, and all those customers leave after the end of that minute.
 * 
 * On some minutes, the bookstore owner is grumpy.  If the bookstore owner is grumpy on the i-th minute, grumpy[i] = 1, otherwise grumpy[i] = 0.  When the bookstore owner is grumpy, the customers of that minute are not satisfied, otherwise they are satisfied.
 * 
 * The bookstore owner knows a secret technique to keep themselves not grumpy for X minutes straight, but can only use it once.
 * 
 * Return the maximum number of customers that can be satisfied throughout the day.
 * 
 * Example 1:
 * Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], X = 3
 * Output: 16
 * Explanation: 
 * The bookstore owner keeps themselves not grumpy for the last 3 minutes. 
 * The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.
 * 
 * Example 2:
 * Input: customers = [1], grumpy = [0], X = 1
 * Output: 1
 * Explanation: 
 * The bookstore owner keeps themselves not grumpy for the last 1 minute. 
 * The maximum number of customers that can be satisfied = 1.
 * 
 * Note:
 * 1. 1 <= X <= customers.length == grumpy.length <= 20000
 * 2. 0 <= customers[i] <= 1000
 * 3. 0 <= grumpy[i] <= 1
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size();
        
        // Step 1: Calculate baseline satisfied customers (when owner is not grumpy)
        int totalSatisfied = 0;
        for (int i = 0; i < n; i++) {
            if (grumpy[i] == 0) {
                totalSatisfied += customers[i];
            }
        }
        
        // Step 2: Find the maximum additional customers we can get by using the technique
        // This means finding a window of length 'minutes' that maximizes the sum of 
        // customers[i] where grumpy[i] == 1
        
        // Calculate initial window sum (first 'minutes' minutes)
        int windowSum = 0;
        for (int i = 0; i < minutes; i++) {
            if (grumpy[i] == 1) {
                windowSum += customers[i];
            }
        }
        
        int maxWindowSum = windowSum;
        
        // Slide the window
        for (int i = minutes; i < n; i++) {
            // Remove leftmost element from window
            if (grumpy[i - minutes] == 1) {
                windowSum -= customers[i - minutes];
            }
            // Add new element to window
            if (grumpy[i] == 1) {
                windowSum += customers[i];
            }
            // Update maximum
            maxWindowSum = max(maxWindowSum, windowSum);
        }
        
        // Step 3: Total = baseline + maximum additional from grumpy minutes
        return totalSatisfied + maxWindowSum;
    }
};

class Solution2 {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size();
        int totalSatisfied = 0;
        int windowSum = 0;
        int maxWindowSum = 0;
        
        for (int i = 0; i < n; i++) {
            // Add to baseline if owner is not grumpy
            if (grumpy[i] == 0) {
                totalSatisfied += customers[i];
            } else {
                // This customer can potentially be saved by the technique
                windowSum += customers[i];
            }
            
            // Maintain window of size 'minutes'
            if (i >= minutes && grumpy[i - minutes] == 1) {
                windowSum -= customers[i - minutes];
            }
            
            // Track maximum window sum
            maxWindowSum = max(maxWindowSum, windowSum);
        }
        
        return totalSatisfied + maxWindowSum;
    }
};