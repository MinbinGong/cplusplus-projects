/*
 * 1353. Maximum Number of Events That Can Be Attended
 * 
 * Given an array of events where events[i] = [startDayi, endDayi]. 
 * Every event i starts at startDayi and ends at endDayi.
 * 
 * You can attend an event i at any day d where startTimei <= d <= endTimei. 
 * Notice that you can only attend one event at any time d.
 * 
 * Return the maximum number of events you can attend.
 * 
 * Example 1:
 * Input: events = [[1,2],[2,3],[3,4]]
 * Output: 3
 * Explanation: You can attend all the three events.
 * One way to attend them all is as shown.
 * Attend the first event on day 1.
 * Attend the second event on day 2.
 * Attend the third event on day 3.
 * 
 * Example 2:
 * Input: events= [[1,2],[2,3],[3,4],[1,2]]
 * Output: 4
 * 
 * Example 3:
 * Input: events = [[1,2],[1,2],[1,6],[1,2],[1,2]]
 * Output: 5
 * 
 * Example 4:
 * Input: events = [[1,2],[1,2],[1,4],[1,2],[1,2]]
 * Output: 4
 * 
 * Note:
 * 1 <= events.length <= 10^5
 * events[i].length == 2
 * 1 <= events[i][0] <= events[i][1] <= 10^5
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        // Sort events by start day
        sort(events.begin(), events.end());
        
        priority_queue<int, vector<int>, greater<int>> minHeap; // end times of available events
        int n = events.size();
        int i = 0;          // index in events
        int ans = 0;
        
        // Iterate over days (1 to 100000, as per constraints)
        for (int day = 1; day <= 100000; ++day) {
            // Add all events that start today
            while (i < n && events[i][0] == day) {
                minHeap.push(events[i][1]);
                ++i;
            }
            
            // Remove events that have already ended (end day < current day)
            while (!minHeap.empty() && minHeap.top() < day) {
                minHeap.pop();
            }
            
            // Attend the event that ends the earliest today
            if (!minHeap.empty()) {
                minHeap.pop();
                ++ans;
            }
            
            // Early exit if no events left
            if (i == n && minHeap.empty()) break;
        }
        
        return ans;
    }
};