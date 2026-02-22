/*
 * Course Schedule III
 * 
 * There are n different online courses numbered from 1 to n. You are given an array courses where courses[i] = [durationi, lastDayi]
 * indicate that the ith course should be taken continuously for durationi days and must be finished before or on lastDayi.
 * 
 * You will start on the 1st day and you cannot take two or more courses simultaneously.
 * 
 * Return the maximum number of courses that you can take.
 * 
 * Example 1:
 * Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
 * Output: 3
 * Explanation: 
 * There are totally 4 courses, but you can take 3 courses at most:
 * First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
 * Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
 * Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day.
 * The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
 * 
 * Example 2:
 * Input: courses = [[1,2]]
 * Output: 1
 * 
 * Example 3:
 * Input: courses = [[3,2],[4,3]]
 * Output: 0
 * Explanation: Both courses cannot be taken.
 * 
 * Constraints:
 * 1 <= n <= 104
 * 1 <= durationi, lastDayi <= 104
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // 按照课程的截止时间升序排序
        sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        // 大根堆，存放已选课程的持续时间
        priority_queue<int> maxHeap;
        int totalTime = 0;

        for (auto& course : courses) {
            int duration = course[0], deadline = course[1];
            // 如果当前课程可以加入，直接加入
            if (totalTime + duration <= deadline) {
                totalTime += duration;
                maxHeap.push(duration);
            }
            // 如果不能加入，但当前课程持续时间比已选最长课程短，则替换
            else if (!maxHeap.empty() && maxHeap.top() > duration) {
                totalTime = totalTime - maxHeap.top() + duration;
                maxHeap.pop();
                maxHeap.push(duration);
            }
        }

        return maxHeap.size();
    }
};