/*
 * 1101. The Earliest Moment When Everyone Become Friends
 * 
 * There are n people in a social group labeled from 0 to n - 1. You are given an array logs where logs[i] = [timestampi, xi, yi] indicates that xi and yi will be friends at the time timestampi.
 * 
 * Friendship is symmetric. That means if a is friends with b, then b is friends with a. Also, person a is acquainted with a person b if a is friends with b, or a is a friend of someone acquainted with b.
 * 
 * Return the earliest time for which every person became acquainted with every other person. If there is no such earliest time, return -1.
 * 
 * 1 <= n <= 100
 * 1 <= logs.length <= 10^4
 * logs[i].length == 3
 * 0 <= timestampi <= 10^9
 * 0 <= xi, yi <= n - 1
 * xi != yi
 * All the values timestampi are unique.
 * All the pairs (xi, yi) occur at most one time in the input.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {
private:
    vector<int> parent, rank;
    int count;  // 当前集合数量
    int time;   // 当前时间戳
    
public:
    UnionFind(int n) : parent(n), rank(n, 1), count(n), time(0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 路径压缩
        }
        return parent[x];
    }
    
    bool unite(int x, int y, int timestamp) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) {
            return false;  // 已经在同一个集合中
        }
        
        // 按秩合并
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        
        count--;           // 集合数量减少
        time = timestamp;  // 更新当前时间戳
        return true;
    }
    
    int getCount() const { return count; }
    int getTime() const { return time; }
};

class Solution {
public:
    int earliestAcq(vector<vector<int>>& logs, int n) {
        // 1. 按时间戳升序排序
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        
        // 2. 初始化并查集
        UnionFind uf(n);
        
        // 3. 按时间顺序处理友谊关系
        for (const auto& log : logs) {
            int timestamp = log[0];
            int x = log[1];
            int y = log[2];
            
            uf.unite(x, y, timestamp);
            
            // 4. 如果所有人都在同一个集合中，返回当前时间戳
            if (uf.getCount() == 1) {
                return timestamp;
            }
        }
        
        // 5. 如果遍历完所有日志后仍然有多个集合，返回-1
        return -1;
    }
};