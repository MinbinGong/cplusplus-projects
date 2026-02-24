/**
 * 871. Minimum Number of Refueling Stops
 * 
 * Example 1:
 * Input: target = 1, startFuel = 1, stations = []
 * Output: 0
 * Explanation: We can reach the target without refueling.
 * 
 * Example 2:
 * Input: target = 100, startFuel = 1, stations = [[10,100]]
 * Output: -1
 * Explanation: We can't reach the target (or even the first gas station).
 * 
 * Example 3:
 * Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
 * Output: 2
 * Explanation: 
 * We start with 10 liters of fuel.
 * We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters to 60 liters of gas.
 * Then, we drive to position 20, expending 10 liters of fuel.  We refuel from 60 liters to 30 liters of gas.
 * Then, we drive to position 30, expending 10 liters of fuel.  We refuel from 30 liters to 10 liters of gas.
 * Then, we drive to position 60, expending 10 liters of fuel.  We refuel from 10 liters to 40 liters of gas.
 * Then, we drive to position 100.  We used a total of 2 refueling stops.
 * 
 * Note:
 * 1 <= target, startFuel, stations[i][1] <= 10^9
 * 0 <= stations.length <= 500
 * 0 < stations[0][0] < stations[1][0] < ... < stations[stations.length-1][0] < target
 * 
 */
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        // Max heap to store fuel amounts from stations we've passed
        priority_queue<int> maxHeap;
        int ans = 0;
        int currFuel = startFuel;
        int prevPos = 0;
        int n = stations.size();

        for (int i = 0; i <= n; ++i) {
            // Current target position: either next station or final target
            int pos = (i < n) ? stations[i][0] : target;
            int need = pos - prevPos;

            // Refuel using largest fuels from heap until we have enough to reach pos
            while (currFuel < need && !maxHeap.empty()) {
                currFuel += maxHeap.top();
                maxHeap.pop();
                ++ans;
            }

            // If still not enough, impossible
            if (currFuel < need) return -1;

            // Travel to pos
            currFuel -= need;

            // After reaching a station, add its fuel to the heap (if not at target)
            if (i < n) {
                maxHeap.push(stations[i][1]);
                prevPos = pos;
            }
        }
        return ans;
    }
};