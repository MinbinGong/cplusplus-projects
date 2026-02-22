/*
 * Task Scheduler
 * 
 * Given a characters array tasks, representing the tasks a CPU needs to do, where each letter represents a different
 * task. Tasks could be done in any order. Each task is done in one unit of time. For each unit of time, the CPU
 * could complete either one task or just be idle.
 * 
 * However, there is a non-negative integer n that represents the cooldown period between two same tasks (the same
 * letter in the array), that is that there must be at least n units of time between any two same tasks.
 * 
 * Return the least number of units of times that the CPU will take to finish all the given tasks.
 * 
 * Example 1:
 * Input: tasks = ["A","A","A","B","B","B"], n = 2
 * Output: 8
 * Explanation: 
 * A -> B -> idle -> A -> B -> idle -> A -> B
 * There is at least 2 units of time between any two same tasks.
 * 
 * Example 2:
 * Input: tasks = ["A","A","A","B","B","B"], n = 0
 * Output: 6
 * Explanation: On this case any permutation of size 6 would work since n = 0.
 * ["A","A","A","B","B","B"]
 * ["A","B","A","B","A","B"]
 * ["B","B","B","A","A","A"]
 * ...
 * And so on.
 * 
 * Example 3:
 * Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
 * Output: 16
 * Explanation: 
 * One possible solution is
 * A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A
 * 
 * Note:
 * 1. The length of the given array won't exceed 1000.
 * 2. The integers in the given array are in the range of [0, 1000].
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // Count frequency of each task (A-Z)
        vector<int> freq(26, 0);
        for (char c : tasks) {
            freq[c - 'A']++;
        }
        
        // Sort in descending order to get the maximum frequency
        sort(freq.begin(), freq.end(), greater<int>());
        
        int maxFreq = freq[0];
        int countMax = 1; // number of tasks with frequency == maxFreq
        
        // Count how many tasks have the same max frequency
        for (int i = 1; i < 26 && freq[i] == maxFreq; ++i) {
            countMax++;
        }
        
        // Formula: (maxFreq - 1) * (n + 1) + countMax
        int requiredTime = (maxFreq - 1) * (n + 1) + countMax;
        int totalTasks = tasks.size();
        
        return max(requiredTime, totalTasks);
    }
};