/*
 * 1436. Destination City
 *
 * You are given the array paths, where paths[i] = [cityAi, cityBi] means there exists a direct path going from cityAi to cityBi. Return the destination city, that is, the city without any path outgoing to another city.
 * 
 * It is guaranteed that the graph of paths forms a line without any loop, therefore, there will be exactly one destination city.
 * 
 * Example 1:
 * 
 * Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
 * Output: "Sao Paulo" 
 * Explanation: Starting at "London" city you will reach "Sao Paulo" city which is the destination city. Your trip consist of: "London" -> "New York" -> "Lima" -> "Sao Paulo".
 * 
 * Example 2:
 * 
 * Input: paths = [["B","C"],["D","B"],["C","A"]]
 * Output: "A"
 * Explanation: All possible trips are: "D" -> "B" -> "C" -> "A". 
 * 
 * Example 3:
 * 
 * Input: paths = [["A","Z"]]
 * Output: "Z"
 * 
 * Note:
 * 1 <= paths.length <= 100
 * paths[i].length == 2
 * 1 <= cityAi.length, cityBi.length <= 10
 * cityAi != cityBi
 * All strings consist of lowercase and uppercase English letters and the space character.
 * 
 */
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        unordered_set<string> startCities;
        // Collect all starting cities
        for (const auto& path : paths) {
            startCities.insert(path[0]);
        }
        // Find the destination city not in starting cities
        for (const auto& path : paths) {
            if (startCities.find(path[1]) == startCities.end()) {
                return path[1];
            }
        }
        return ""; // should never reach here due to problem constraints
    }
};
