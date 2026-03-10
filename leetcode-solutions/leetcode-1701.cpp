/**
 * 1701. Average Waiting Time
 * 
 * Given a list of customers where each customer is represented as a pair of integers (arrival time, service time),
 * return the average waiting time of all customers.
 * 
 * Example 1:
 * Input: customers = {{1,2},{2,5},{4,3}}
 * Output: 5.00000
 * Explanation:
 * 1) The first customer arrives at time 1, the chef takes his order and starts preparing it immediately at time 1,
 *    and finishes at time 3, so the waiting time of the first customer is 3 - 1 = 2.
 * 2) The second customer arrives at time 2, the chef takes his order and starts preparing it at time 3,
 *    and finishes at time 8, so the waiting time of the second customer is 8 - 2 = 6.
 * 3) The third customer arrives at time 4, the chef takes his order and starts preparing it at time 8,
 *    and finishes at time 11, so the waiting time of the third customer is 11 - 4 = 7.
 * Hence, the average waiting time is (2 + 6 + 7) / 3 = 5.00000.
 * 
 * Example 2:
 * Input: customers = {{5,2},{5,4},{10,3},{20,1}}
 * Output: 3.25000
 * Explanation:
 * 1) The first customer arrives at time 5, the chef takes his order and starts preparing it immediately at time 5,
 *    and finishes at time 7, so the waiting time of the first customer is 7 - 5 = 2.
 * 2) The second customer arrives at time 5, the chef takes his order and starts preparing it at time 7,
 *    and finishes at time 11, so the waiting time of the second customer is 11 - 5 = 6.
 * 3) The third customer arrives at time 10, the chef takes his order and starts preparing it at time 11,
 *    and finishes at time 14, so the waiting time of the third customer is 14 - 10 = 4.
 * 4) The fourth customer arrives at time 20, the chef takes his order and starts preparing it immediately at time 20,
 *    and finishes at time 21, so the waiting time of the fourth customer is 21 - 20 = 1.
 * Hence, the average waiting time is (2 + 6 + 4 + 1) / 4 = 3.25000.
 * 
 * Constraints:
 * 1 <= customers.length <= 10^5
 * 1 <= arrival time, service time <= 10^4
 * arrival time <= service time
 * 
 */
#include <vector>
#include <algorithm> // for max

class Solution {
public:
    double averageWaitingTime(std::vector<std::vector<int>>& customers) {
        long long total_wait = 0;  // use long long to avoid overflow
        int current_time = 0;       // time when chef becomes free

        for (const auto& c : customers) {
            int arrival = c[0];
            int prep_time = c[1];

            // Start time is the later of current_time and arrival
            int start = std::max(current_time, arrival);
            int finish = start + prep_time;

            total_wait += (finish - arrival);
            current_time = finish;
        }

        int n = customers.size();
        return static_cast<double>(total_wait) / n;
    }
};