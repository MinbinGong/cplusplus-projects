/*
 * 1606. Find Servers That Handled Most Number of Requests
 *
 * You have k servers numbered from 0 to k-1 that are being used to handle multiple requests simultaneously. Each server has infinite computational capacity but cannot handle more than one request at a time. The requests are assigned to servers according to a specific algorithm:
 *
 * The ith (0-indexed) request arrives.
 * If all servers are busy, the request is dropped (not handled at all).
 * If the (i % k)th server is available, assign the request to that server.
 * Otherwise, assign the request to the next available server (wrapping around the list of servers and starting from 0 if necessary). For example, if the ith server is busy, try to assign the request to the (i+1)th server, then the (i+2)th server, and so on. 
 * 
 * Example 1:
 * Input: k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3] 
 * Output: [1,2,0] 
 * Explanation: 
 * All of the servers start out available.
 * The first 3 requests are handled by the first 3 servers in order.
 * Request 3 comes in. Server 0 is busy, so it's assigned to the next available server, which is 1.
 * Request 4 comes in. It cannot be handled since all servers are busy, so it is dropped.
 * Request 5 comes in. It cannot be handled since all servers are busy, so it is dropped.
 * 
 * Example 2:
 * Input: k = 3, arrival = [1,2,3,4], load = [1,2,1,2]
 * Output: [0,2,1]
 * Explanation: 
 * All servers are busy.
 * The requests are handled by the first 3 servers in order.
 * Request 3 comes in. It cannot be handled since all servers are busy, so it is dropped.
 * 
 * 
 * Constraints:
 * 1 <= k <= 105
 * 1 <= arrival.length, load.length <= 105
 * arrival.length == load.length
 * 0 <= arrival[i], load[i] <= 105
 * arrival is strictly increasing.
 * 
 */
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> count(k, 0);
        set<int> available;
        for (int i = 0; i < k; ++i) available.insert(i);
        
        // min-heap of (finish_time, server_id)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> busy;
        
        int n = arrival.size();
        for (int i = 0; i < n; ++i) {
            int start = arrival[i];
            int duration = load[i];
            
            // free servers that have finished by this request's arrival
            while (!busy.empty() && busy.top().first <= start) {
                int server = busy.top().second;
                busy.pop();
                available.insert(server);
            }
            
            if (available.empty()) {
                continue; // drop the request
            }
            
            // find the first available server with index >= i % k
            int target = i % k;
            auto it = available.lower_bound(target);
            if (it == available.end()) {
                // wrap around to the smallest available
                it = available.begin();
            }
            int server = *it;
            available.erase(it);
            
            // record the finish time
            busy.push({start + duration, server});
            count[server]++;
        }
        
        // find maximum count
        int maxCount = *max_element(count.begin(), count.end());
        vector<int> result;
        for (int i = 0; i < k; ++i) {
            if (count[i] == maxCount) {
                result.push_back(i);
            }
        }
        return result;
    }
};