/*
 * 957. Prison Cells After N Days
 *
 * There are 8 prison cells in a row and each cell is either occupied or vacant.
 *
 * Each day, whether the cell is occupied or vacant changes according to the following rules:
 *
 * If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.
 * Otherwise, it becomes vacant.
 * Note that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.
 *
 * You are given an integer array cells where cells[i] == 1 if the ith cell is occupied and cells[i] == 0 if the ith cell is vacant, and you are given an integer n.
 *
 * Return the state of the prison after n days (i.e., n such changes described above).
 *
 * Example 1:
 *
 * Input: cells = [0,1,0,1,1,0,0,1], n = 7
 * Output: [0,0,1,1,0,0,0,0]
 * 
 * Example 2:
 *
 * Input: cells = [1,0,0,1,0,0,1,0], n = 1000000000
 * Output: [0,0,1,1,1,1,1,0]
 * 
 * Note:
 *
 * 1 <= cells.length <= 100
 * cells[i] is either 0 or 1.
 * 1 <= n <= 109
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        // 用于记录每个状态第一次出现的天数
        unordered_map<string, int> seen;
        bool hasCycle = false;

        for (int day = 0; day < N; ++day) {
            // 计算下一天的状态
            vector<int> next(8, 0);
            for (int i = 1; i < 7; ++i) {
                next[i] = (cells[i-1] == cells[i+1]) ? 1 : 0;
            }

            // 将状态转换为字符串，作为哈希表的键
            string key(next.begin(), next.end());

            // 检查是否出现循环
            if (seen.count(key)) {
                // 找到循环，计算循环长度并跳过剩余天数
                int cycleLength = day - seen[key];
                int remainingDays = (N - day - 1) % cycleLength;
                // 递归或循环处理剩余天数
                return prisonAfterNDays(next, remainingDays);
            } else {
                // 未出现循环，记录当前状态
                seen[key] = day;
            }

            // 更新 cells 为下一天的状态
            cells = next;
        }

        return cells;
    }
};