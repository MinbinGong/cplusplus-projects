/*
 * 1094. Car Pooling
 *
 * There is a car with capacity empty seats.  The vehicle only drives east (ie. it cannot turn around and drive west.)
 * Given the array trips, where trips[i] = [num_passengers, start_location, end_location] contains information about the i-th trip:
 * the number of passengers that must be picked up, and the locations to pick them up and drop them off.
 * The locations are given as the number of kilometers due east from the car's initial location.
 * Return true if and only if it is possible to pick up and drop off all passengers for all the given trips.
 * 
 * Example 1:
 * Input: trips = [[2,1,5],[3,3,7]], capacity = 4
 * Output: false
 * 
 * Example 2:
 * Input: trips = [[2,1,5],[3,3,7]], capacity = 5
 * Output: true
 * 
 * Example 3:
 * Input: trips = [[2,1,5],[3,5,7]], capacity = 3
 * Output: true
 *
 * Note:
 * 1 <= trips.length <= 1000
 * trips[i].length == 3
 * 1 <= trips[i][0] <= 100
 * 0 <= trips[i][1] < trips[i][2] <= 1000
 * 1 <= capacity <= 100000
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // 因为位置范围是 0 到 1000，可以直接用固定大小的数组
        vector<int> diff(1001, 0);
        
        // 构建差分数组
        for (const auto& trip : trips) {
            int num = trip[0];      // 乘客数
            int start = trip[1];    // 上车点
            int end = trip[2];      // 下车点
            diff[start] += num;     // 上车增加乘客
            diff[end] -= num;       // 下车减少乘客
        }
        
        // 前缀和模拟当前车上人数
        int cur = 0;
        for (int i = 0; i <= 1000; ++i) {
            cur += diff[i];
            if (cur > capacity) {   // 超载
                return false;
            }
        }
        return true;
    }
};