/*
 * 1196. How Many Apples Can You Put into the Basket
 *
 * You have some apples, where arr[i] is the weight of the i-th apple.  You also have a basket that can carry up to 5000 units of weight.
 * 
 * Return the maximum number of apples you can put in the basket.
 * 
 * Example 1:
 * Input: arr = [100,200,150,1000]
 * Output: 4
 * Explanation: All 4 apples can be carried by the basket since their sum of weights is 1450.
 * 
 * Example 2:
 * Input: arr = [900,950,800,1000,700,800]
 * Output: 5
 * Explanation: The sum of weights of the 6 apples exceeds 5000 so we choose any 5 of them.
 * 
 * Note:
 * 1 <= arr.length <= 10^3
 * 1 <= arr[i] <= 10^3
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxNumberOfApples(vector<int>& weight) {
        // Sort the apples by weight so we can take the lightest ones first
        sort(weight.begin(), weight.end());
        
        int totalWeight = 0;
        int count = 0;
        
        for (int w : weight) {
            if (totalWeight + w <= 5000) {
                totalWeight += w;
                ++count;
            } else {
                break; // cannot take any more apples
            }
        }
        
        return count;
    }
};