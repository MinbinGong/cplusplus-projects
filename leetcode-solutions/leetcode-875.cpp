/**
 * 875. Koko Eating Bananas
 * 
 * Example 1:
 * Input: piles = [3,6,7,11], H = 8
 * Output: 4
 * 
 * Example 2:
 * Input: piles = [30,11,23,4,20], H = 5
 * Output: 30
 * 
 * Example 3:
 * Input: piles = [30,11,23,4,20], H = 6
 * Output: 23
 * 
 * Note:
 * 1 <= piles.length <= 10^4
 * piles.length <= H <= 10^9
 * 1 <= piles[i] <= 10^9
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1, right = *max_element(piles.begin(), piles.end());
        while (left < right) {
            int mid = left + (right - left) / 2;
            long long hours = 0;
            for (int p : piles) {
                hours += (p + mid - 1) / mid; // 等价于 ceil(p / mid)
            }
            if (hours <= h) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};