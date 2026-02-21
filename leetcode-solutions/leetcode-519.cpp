/*
 * Random Flip Matrix
 *
 * You are given the number of rows n_rows and number of columns n_cols of a 2D binary matrix where all values are initially 0. Write a function flip which chooses a 0 value uniformly at random, changes it to 1, and then returns the position [row.id, col.id] of that value. Also, write a function reset which sets all values back to 0. Try to minimize the number of calls to system's Math.random() and optimize the time and space complexity.
 * 
 * Note:
 * 1 <= n_rows, n_cols <= 10000
 * 0 <= row.id < n_rows and 0 <= col.id < n_cols
 * flip will not be called when the matrix has no 0 values left.
 * the total number of calls to flip and reset will not exceed 1000.
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
private:
    int rows, cols;
    int total;                     // number of remaining zero cells
    unordered_map<int, int> mp;    // maps a chosen index to the actual unused index

public:
    Solution(int m, int n) {
        rows = m;
        cols = n;
        total = m * n;
    }
    
    vector<int> flip() {
        // generate random index in [0, total-1]
        int x = rand() % total;
        
        // get the actual unused index corresponding to x
        int idx = mp.count(x) ? mp[x] : x;
        
        // map x to the current last index (total-1)
        if (mp.count(total - 1)) {
            mp[x] = mp[total - 1];
            mp.erase(total - 1);   // last index is no longer available
        } else {
            mp[x] = total - 1;
        }
        
        total--;   // one less zero cell
        
        // convert linear index to 2D coordinates
        return {idx / cols, idx % cols};
    }
    
    void reset() {
        total = rows * cols;
        mp.clear();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */