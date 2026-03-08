/*
 * 1665. Minimum Initial Energy to Finish Tasks
 *
 * You are given an array tasks where tasks[i] = [actuali, minimumi]:
 * 
 * actuali is the actual amount of energy you spend to finish the ith task.
 * minimumi is the minimum amount of energy you require to begin the ith task.
 * For example, if the task is [10, 12] and your current energy is 11, you cannot start this task. However, if your current energy is 13, you can complete this task, and your energy will be 3 after finishing it.
 * 
 * You can finish the tasks in any order you like.
 * 
 * Return the minimum initial amount of energy you will need to finish all the tasks.
 * 
 * Example 1:
 * Input: tasks = [[1,2],[2,4],[4,8]]
 * Output: 8
 * Explanation:
 * Starting with 8 energy, we finish the tasks in the following order:
 *     - 3rd task. Now energy = 8 - 4 = 4.
 *     - 2nd task. Now energy = 4 - 2 = 2.
 *     - 1st task. Now energy = 2 - 1 = 1.
 * Notice that even though we have leftover energy, we cannot start the 3rd task.
 * 
 * Example 2:
 * Input: tasks = [[1,3],[2,4],[10,11],[10,12],[8,9]]
 * Output: 32
 * Explanation:
 * Starting with 32 energy, we finish the tasks in the following order:
 *     - 1st task. Now energy = 32 - 1 = 31.
 *     - 2nd task. Now energy = 31 - 2 = 29.
 *     - 3rd task. Now energy = 29 - 10 = 19.
 *     - 4th task. Now energy = 19 - 10 = 9.
 *     - 5th task. Now energy = 9 - 8 = 1.
 * 
 * Constraints:
 * 1 <= tasks.length <= 104
 * 1 <= actuali, minimumi <= 104
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // 按照 (minimum - actual) 的差值升序排序
        // 差值小的任务先做，这样能最小化所需的初始能量
        sort(tasks.begin(), tasks.end(), 
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] - a[0] < b[1] - b[0];
             });
        
        int ans = 0;      // 所需的最小初始能量
        int cur = 0;      // 当前能量
        
        for (const auto& task : tasks) {
            int actual = task[0];   // 任务实际消耗
            int minimum = task[1];   // 任务开始所需最低能量
            
            // 如果当前能量不足以开始这个任务，需要补充能量
            if (cur < minimum) {
                ans += minimum - cur;   // 增加初始能量
                cur = minimum;           // 当前能量提升到最低要求
            }
            
            // 执行任务，消耗能量
            cur -= actual;
        }
        
        return ans;
    }
};

class Solution2 {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // 按 (minimum - actual) 升序排序
        sort(tasks.begin(), tasks.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] - a[0] < b[1] - b[0];
             });
        
        int ans = 0;
        int sumActual = 0;  // 已选任务的实际消耗总和
        
        for (const auto& task : tasks) {
            int actual = task[0];
            int minimum = task[1];
            
            // 关键公式：ans = max(ans, sumActual + minimum)
            // 表示到当前任务为止，所需的最小初始能量
            ans = max(ans, sumActual + minimum);
            sumActual += actual;
        }
        
        return ans;
    }
};