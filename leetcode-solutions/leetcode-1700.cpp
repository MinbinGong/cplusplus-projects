/*
 * 1700. Number of Students Unable to Eat Lunch
 * 
 * The school cafeteria offers circular and square sandwiches at lunch break, referred to by numbers 0 and 1 respectively. All students stand in a queue. Each student either prefers square or circular sandwiches.
 * 
 * The number of sandwiches in the cafeteria is equal to the number of students. The sandwiches are placed in a stack. At each step:
 * If the student at the front of the queue prefers the sandwich on the top of the stack, they will take it and leave the queue.
 * Otherwise, they will leave it and go to the queue's end.
 * This continues until none of the queue students want to take the top sandwich and are thus unable to eat.
 * 
 * Given two integer arrays students and sandwiches where sandwiches[i] is the type of the i​​​​​​th sandwich in the stack (i = 0 is the top of the stack) and students[j] is the preference of the j​​​​​​th student in the initial queue (j = 0 is the front of the queue). Return the number of students that are unable to eat.
 * 
 * Example 1:
 * Input: students = [1,1,0,0], sandwiches = [0,1,0,1]
 * Output: 0 
 * Explanation:
 * - Front student leaves the top sandwich and returns to the end of the line making students = [1,0,0,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [0,0,1,1].
 * - Front student takes the top sandwich and leaves the line making students = [0,1,1] and sandwiches = [1,0,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [1,1,0].
 * - Front student takes the top sandwich and leaves the line making students = [1,0] and sandwiches = [0,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [0,1].
 * - Front student takes the top sandwich and leaves the line making students = [1] and sandwiches = [1].
 * - Front student takes the top sandwich and leaves the line making students = [] and sandwiches = [].
 * Hence all students are able to eat.
 * 
 * Example 2:
 * Input: students = [1,1,1,0,0,1], sandwiches = [1,0,0,0,1,1]
 * Output: 3
 * Explanation:
 * - Front student leaves the top sandwich and returns to the end of the line making students = [1,1,0,0,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [1,0,0,1,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [0,0,1,1,1].
 * - Front student takes the top sandwich and leaves the line making students = [0,1,1,1] and sandwiches = [0,0,1,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [1,1,1,0].
 * - Front student takes the top sandwich and leaves the line making students = [1,1,0] and sandwiches = [0,1,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [1,0,1].
 * - Front student takes the top sandwich and leaves the line making students = [0,1] and sandwiches = [1,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [1,0,1].
 * - Front student takes the top sandwich and leaves the line making students = [0,1] and sandwiches = [1,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [1,0,1].
 * - Front student takes the top sandwich and leaves the line making students = [0,1] and sandwiches = [1,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [1,0,1].
 * - Front student takes the top sandwich and leaves the line making students = [0,1] and sandwiches = [1,1].
 * - Front student leaves the top sandwich and returns to the end of the line making students = [1,0,1].
 * - Front student takes the top sandwich and leaves the line making students = [0,1] and sandwiches = [1,1].
 * - Front student takes the top sandwich and leaves the line making students = [1] and sandwiches = [1].
 * - Front student takes the top sandwich and leaves the line making students = [] and sandwiches = [].
 * Hence three students are unable to eat.
 * 
 * Constraints:
 * 1 <= students.length, sandwiches.length <= 100
 * students.length == sandwiches.length
 * sandwiches[i] is 0 or 1.
 * students[i] is 0 or 1.
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution1 {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int count[2] = {0, 0}; // count[0]: 喜欢圆形的学生数, count[1]: 喜欢方形的学生数
        
        // 统计喜欢圆形和方形的学生数量
        for (int student : students) {
            count[student]++;
        }
        
        // 遍历三明治栈
        for (int sandwich : sandwiches) {
            // 如果没有学生喜欢当前类型的三明治，停止分发
            if (count[sandwich] == 0) {
                break;
            }
            // 有一个学生拿到三明治离开
            count[sandwich]--;
        }
        
        // 剩余无法吃到午餐的学生数
        return count[0] + count[1];
    }
};

class Solution2 {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        queue<int> q;
        for (int student : students) {
            q.push(student);
        }
        
        int i = 0; // 三明治索引
        int failedAttempts = 0; // 连续失败的尝试次数
        
        while (!q.empty() && failedAttempts < q.size()) {
            int student = q.front();
            q.pop();
            
            if (student == sandwiches[i]) {
                // 学生拿到三明治
                i++;
                failedAttempts = 0; // 重置失败计数
            } else {
                // 学生放回队列末尾
                q.push(student);
                failedAttempts++;
            }
        }
        
        return q.size();
    }
};