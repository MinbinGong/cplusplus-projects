/*
 * Kill Process
 *
 * Given n processes, each process has a unique PID (process id) and its PPID (parent process id).
 * 
 * Note:
 * Each process only has one parent process, but may have one or more children processes.
 * None of the input PID or PPID is 0.
 * 
 * Example:
 * Input: 
 * pid =  [1, 3, 10, 5]
 * ppid = [3, 0, 5, 3]
 * kill = 5
 * Output: [5,10]
 * Explanation: 
 *            3
 *          /   \
 *         1     5
 *              /
 *             10
 * Kill 5 will also kill 10.
 * 
 */
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, vector<int>> children;
        // Build mapping from parent to list of children
        for (int i = 0; i < pid.size(); ++i) {
            children[ppid[i]].push_back(pid[i]);
        }
        
        vector<int> result;
        stack<int> stk;
        stk.push(kill);
        
        // DFS traversal
        while (!stk.empty()) {
            int curr = stk.top();
            stk.pop();
            result.push_back(curr);
            for (int child : children[curr]) {
                stk.push(child);
            }
        }
        return result;
    }
};