/*
 * 1705. Maximum Number of Eaten Apples
 * 
 * There is a special kind of apple tree that grows apples every day for n days. On the ith day, the tree grows apples[i] apples that will rot after days[i] days, that is on day i + days[i] the apples will be rotten and cannot be eaten. On some days, the apple tree does not grow any apples, which are denoted by apples[i] == 0 and days[i] == 0.
 * 
 * You decided to eat at most one apple a day (to keep the doctors away). Note that you can keep eating after the first n days.
 * 
 * Given two integer arrays days and apples of length n, return the maximum number of apples you can eat.
 * 
 * Example 1:
 * Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
 * Output: 7
 * Explanation: You can eat 7 apples:
 * - On the first day, you eat an apple that grew on the first day.
 * - On the second day, you eat an apple that grew on the second day.
 * - On the third day, you eat an apple that grew on the second day.
 * - On the fourth to the seventh days, you eat apples that grew on the fourth day.
 * 
 * Example 2:
 * Input: apples = [3,0,0,0,0,2], days = [3,0,0,0,0,2]
 * Output: 5
 * Explanation: You can eat 5 apples:
 * - On the first to the fifth days, you eat apples that grew on the first day.
 * - On the sixth and seventh days, you eat apples that grew on the sixth day.
 * 
 * Constraints:
 * n == apples.length == days.length
 * 1 <= n <= 2 * 10^4
 * 0 <= apples[i], days[i] <= 2 * 10^4
 * days[i] = 0 if and only if apples[i] = 0.
 * 
 */
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int n = apples.size();
        // min‑heap of rotten days
        priority_queue<int, vector<int>, greater<int>> pq;
        // number of apples that rot on a particular day
        unordered_map<int, int> count;
        int ans = 0;
        int day = 0;

        while (day < n || !pq.empty()) {
            // add today's harvest (if any)
            if (day < n && apples[day] > 0) {
                int rot = day + days[day];
                count[rot] += apples[day];
                pq.push(rot);
            }

            // remove all rotten apples (rot day ≤ current day)
            while (!pq.empty() && pq.top() <= day) {
                int r = pq.top();
                pq.pop();
                count.erase(r);
            }

            // discard entries that have already been fully eaten
            while (!pq.empty() && count[pq.top()] == 0) {
                pq.pop();
            }

            // eat one apple from the batch that rots the earliest
            if (!pq.empty()) {
                int r = pq.top();
                ++ans;
                --count[r];
                // if count becomes zero, it will be cleaned up later
            }

            ++day;
        }

        return ans;
    }
};