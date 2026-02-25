/*
 * 1029. Two City Scheduling
 *
 * There are 2N people a company is planning to interview. The cost of flying the i-th person to city A is costs[i][0], and the cost of flying the i-th person to city B is costs[i][1].
 *
 * Return the minimum cost to fly every person to a city such that exactly N people arrive in each city.
 *
 * Example 1:
 *
 * Input: [[10,20],[30,200],[400,50],[30,20]]
 * Output: 110
 * Explanation: 
 * The first person goes to city A for a cost of 10.
 * The second person goes to city A for a cost of 30.
 * The third person goes to city B for a cost of 50.
 * The fourth person goes to city B for a cost of 20.
 *
 * The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.
 * 
 * Example 2:
 *
 * Input: [[259,770],[448,54],[926,667],[184,139],[840,118],[577,469]]
 * Output: 1859
 * 
 * Example 3:
 *
 * Input: [[515,563],[451,713],[537,709],[343,819],[855,779],[457,60],[650,359],[631,42]]
 * Output: 3086
 * 
 * Note:
 * 
 * 2 <= costs.length <= 100
 * costs.length is even.
 * 1 <= costs[i][0], costs[i][1] <= 1000
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        // Sort by the difference between cost to A and cost to B
        sort(costs.begin(), costs.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return (a[0] - a[1]) < (b[0] - b[1]);
             });

        int total = 0;
        int n = costs.size() / 2;
        // First N people go to city A, rest to city B
        for (int i = 0; i < n; ++i) {
            total += costs[i][0] + costs[i + n][1];
        }
        return total;
    }
};