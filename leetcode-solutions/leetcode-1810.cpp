/*
 * 1810. Maximum Number of Nice Divisors
 *
 * You are given a positive integer primeFactors. You are asked to construct a positive integer n that satisfies the following conditions:
 * 
 * The number of prime factors of n (not necessarily distinct) is at most primeFactors.
 * The number of nice divisors of n is maximized. Note that a divisor of n is nice if it is divisible by every prime factor of n. For example, if n = 12, then its prime factors are [2,2,3], then 6 and 12 are nice divisors, while 3 and 4 are not.
 * Return the number of nice divisors of n. Since that number can be too large, return it modulo 109 + 7.
 * 
 * Example 1:
 * 
 * Input: primeFactors = 5
 * Output: 6
 * Explanation: 200 is a valid value of n.
 * 
 * Example 2:
 * 
 * Input: primeFactors = 8
 * Output: 18
 * Explanation: 280 is a valid value of n, and it has more nice divisors than 200.
 * 
 * Constraints:
 * 
 * 1 <= primeFactors <= 109
 * 
 */
/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 * public:
 *   bool canMove(char direction);
 *   int move(char direction);
 *   boolean isTarget();
 * };
 */
#include <vector>
#include <numeric> // for iota
#include <unordered_map>
using namespace std;

class Solution {
private:
    // 方向映射：当前方向 -> (行偏移, 列偏移, 相反方向)
    const vector<pair<char, pair<int, int>>> dirs = {
        {'U', {-1, 0}},
        {'D', {1, 0}},
        {'L', {0, -1}},
        {'R', {0, 1}}
    };
    // 相反方向查找表
    const unordered_map<char, char> opposite = {
        {'U', 'D'}, {'D', 'U'}, {'L', 'R'}, {'R', 'L'}
    };
    
    static constexpr int N = 200;          // 假设网格最大为 200x200
    static constexpr int START = 100;      // 起点设在中心 (100, 100)
    vector<vector<int>> grid;               // 记录每个格子的消耗，-1表示未访问/不可达
    vector<vector<int>> dist;                // Dijkstra 的距离数组
    int targetX = -1, targetY = -1;          // 目标坐标

public:
    int findShortestPath(GridMaster& master) {
        // 初始化
        grid.assign(N, vector<int>(N, -1));
        dist.assign(N, vector<int>(N, INT_MAX));
        
        // 第一阶段：DFS 探索，从起点开始
        grid[START][START] = 0;  // 起点消耗为 0（不计入总消耗）
        dfs(master, START, START);
        
        // 如果没找到目标，返回 -1
        if (targetX == -1 || targetY == -1) {
            return -1;
        }
        
        // 第二阶段：Dijkstra 求最短路径
        return dijkstra();
    }

private:
    void dfs(GridMaster& master, int x, int y) {
        // 检查当前位置是否是目标
        if (master.isTarget()) {
            targetX = x;
            targetY = y;
        }
        
        // 尝试四个方向
        for (const auto& [d, delta] : dirs) {
            int nx = x + delta.first;
            int ny = y + delta.second;
            
            // 如果该方向可以移动，且该格子尚未探索过
            if (nx >= 0 && nx < N && ny >= 0 && ny < N && 
                master.canMove(d) && grid[nx][ny] == -1) {
                
                // 移动到新格子，并记录消耗
                int cost = master.move(d);
                grid[nx][ny] = cost;
                
                // 递归探索
                dfs(master, nx, ny);
                
                // 回溯：移动回原位置
                master.move(opposite.at(d));
            }
        }
    }
    
    int dijkstra() {
        // 优先队列：存储 (当前总消耗, x, y)
        using Node = tuple<int, int, int>;
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        
        pq.emplace(0, START, START);
        dist[START][START] = 0;
        
        while (!pq.empty()) {
            auto [cost, x, y] = pq.top();
            pq.pop();
            
            // 如果已经到达目标
            if (x == targetX && y == targetY) {
                return cost;
            }
            
            // 如果当前记录的距离已经小于 cost，跳过（Dijkstra 优化）
            if (cost > dist[x][y]) {
                continue;
            }
            
            // 遍历四个相邻格子
            for (const auto& [_, delta] : dirs) {
                int nx = x + delta.first;
                int ny = y + delta.second;
                
                // 检查边界和是否可走（grid[nx][ny] != -1）
                if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] != -1) {
                    int newCost = cost + grid[nx][ny];
                    if (newCost < dist[nx][ny]) {
                        dist[nx][ny] = newCost;
                        pq.emplace(newCost, nx, ny);
                    }
                }
            }
        }
        
        return -1; // 理论上不会执行到这里，因为之前已检查目标可达
    }
};