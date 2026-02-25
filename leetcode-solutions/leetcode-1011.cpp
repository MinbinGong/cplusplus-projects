/*
 * 1011. Capacity To Ship Packages Within D Days
 *
 * A conveyor belt has packages that must be shipped from one port to another within D days.
 *
 * The i-th package on the conveyor belt has a weight of weights[i].  Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.
 *
 * Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within D days.
 *
 * Example 1:
 *
 * Input: weights = [1,2,3,4,5,6,7,8,9,10], D = 5
 * Output: 15
 * Explanation: 
 * A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
 * 1st day: 1, 2, 3, 4, 5
 * 2nd day: 6, 7
 * 3rd day: 8
 * 4th day: 9
 * 5th day: 10
 * 
 * Note:
 *
 * 1 <= D <= weights.length <= 50000
 * 1 <= weights[i] <= 500
 * 
 */
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int left = *max_element(weights.begin(), weights.end()); // at least max weight
        int right = accumulate(weights.begin(), weights.end(), 0); // at most total weight

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canShip(weights, days, mid)) {
                right = mid; // try smaller capacity
            } else {
                left = mid + 1; // need larger capacity
            }
        }
        return left;
    }

private:
    bool canShip(vector<int>& weights, int days, int capacity) {
        int dayCount = 1;
        int currentLoad = 0;
        for (int w : weights) {
            if (currentLoad + w > capacity) {
                dayCount++;
                currentLoad = w;
                if (dayCount > days) return false;
            } else {
                currentLoad += w;
            }
        }
        return true;
    }
};