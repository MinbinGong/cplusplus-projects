/*
 *  Teemo Attacking
 *
 *  In LOL world, there is a hero called Teemo and his attacking can make his enemy Ashe be in poisoned condition. Now, given the Teemo's attacking ascending time series towards Ashe and the poisoning time duration per Teemo's attacking, you need to output the total time that Ashe is in poisoned condition.
 *
 *  You may assume that Teemo attacks at the very beginning of a specific time point, and makes Ashe be in poisoned condition immediately.
 *
 *  Constraints:
 *  1 <= timeSeries.length <= 104
 *  0 <= timeSeries[i], duration <= 107
 *  timeSeries is sorted by ascending order.
 * 
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (timeSeries.empty()) return 0;
        int total = 0;
        for (int i = 0; i < timeSeries.size() - 1; ++i) {
            total += min(duration, timeSeries[i + 1] - timeSeries[i]);
        }
        total += duration; // last attack always lasts full duration
        return total;
    }
};