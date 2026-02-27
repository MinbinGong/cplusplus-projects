/*
 * 1086. High Five
 *
 * Given a list of scores of different students, return the average score of each student's top five scores in the order of each student's id.
 * Each entry items[i] has items[i][0] the student's id, and items[i][1] the student's score.  The average score is calculated using integer division.
 * 
 * Example 1:
 * Input: [[1,91],[1,92],[2,93],[2,97],[1,60],[2,77],[1,65],[1,87],[1,100],[2,100],[2,76]]
 * Output: [[1,87],[2,88]]
 * Explanation: 
 * The average of the student with id = 1 is 87.
 * The average of the student with id = 2 is 88.6. But with integer division their average converts to 88.
 * 
 * Note:
 * 1 <= items.length <= 1000
 * items[i].length == 2
 * 1 <= items[i][0] <= 1000
 * 1 <= items[i][1] <= 100
 * 
 */
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> highFive(vector<vector<int>>& items) {
        // 哈希表：key为学生ID，value为最小堆（存储分数）
        unordered_map<int, priority_queue<int, vector<int>, greater<int>>> studentScores;
        
        // 遍历所有成绩记录
        for (const auto& item : items) {
            int id = item[0];
            int score = item[1];
            
            // 获取或创建该学生的分数堆
            auto& minHeap = studentScores[id];
            
            // 将分数加入最小堆
            minHeap.push(score);
            
            // 如果堆大小超过5，移除最小的分数（保持最大的5个分数）
            if (minHeap.size() > 5) {
                minHeap.pop();
            }
        }
        
        // 准备结果
        vector<vector<int>> result;
        
        // 遍历哈希表，计算每个学生的平均分
        for (auto& [id, minHeap] : studentScores) {
            int sum = 0;
            
            // 计算堆中所有分数的和（已经是最大的5个分数）
            while (!minHeap.empty()) {
                sum += minHeap.top();
                minHeap.pop();
            }
            
            // 计算平均值（向下取整）
            int average = sum / 5;
            
            // 添加到结果
            result.push_back({id, average});
        }
        
        // 按学生ID升序排序
        sort(result.begin(), result.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        
        return result;
    }
};