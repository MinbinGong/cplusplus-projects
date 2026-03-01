/**
 * 1298. Maximum Candies You Can Get from Boxes
 * 
 * Given n boxes, each box is given in the format [status, candies, keys, containedBoxes] where:
 * status[i]: an integer which is 1 if box[i] is open and 0 if box[i] is closed.
 * candies[i]: an integer representing the number of candies in box[i].
 * keys[i]: an array contains the indices of the boxes you can open with the key in box[i].
 * containedBoxes[i]: an array contains the indices of the boxes found in box[i].
 * 
 * You will start with some boxes given in initialBoxes array. You can take all the candies in any open box and you can use the keys in it to open new boxes and you also can use the boxes you find in it.
 * Return the maximum number of candies you can get following the rules above.
 * 
 * Example 1:
 * Input: status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]], containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
 * Output: 16
 * Explanation: You will be initially given box 0. You will find 7 candies in it and boxes 1 and 2. Box 1 is closed and you don't have a key for it so you will open box 2. You will find 4 candies and a key to box 1 in box 2.
 * In box 1, you will find 5 candies and box 3 but you will not find a key to box 3 so box 3 will remain closed.
 * Total number of candies collected = 7 + 4 + 5 = 16 candy.
 * 
 * Example 2:
 * Input: status = [1,0,0,0,0,0], candies = [1,1,1,1,1,1], keys = [[1,2,3,4,5],[],[],[],[],[]], containedBoxes = [[1,2,3,4,5],[],[],[],[],[]], initialBoxes = [0]
 * Output: 6
 * Explanation: You have initially box 0. Opening it you can find boxes 1,2,3,4 and 5 and their keys. The total number of candies will be 6.
 * 
 * Example 3:
 * Input: status = [1,1,1], candies = [100,1,100], keys = [[],[0,2],[]], containedBoxes = [[],[],[]], initialBoxes = [1]
 * Output: 1
 * 
 * Example 4:
 * Input: status = [1], candies = [100], keys = [[]], containedBoxes = [[]], initialBoxes = []
 * Output: 0
 * 
 * Note:
 * 1 <= status.length <= 1000
 * 1 <= candies.length <= 1000
 * 1 <= keys.length <= 1000
 * keys[i].length <= 1000
 * 0 <= containedBoxes[i].length <= 1000
 * 0 <= initialBoxes.length <= 1000
 * 0 <= keys[i][j], containedBoxes[i][j] < status.length
 * All values in keys[i] are unique.
 * 
 */
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution1 {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, 
                   vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, 
                   vector<int>& initialBoxes) {
        int n = status.size();
        int ans = 0;
        
        // 记录是否拥有某个盒子
        vector<bool> has(n, false);
        // 记录是否已经打开过某个盒子
        vector<bool> opened(n, false);
        
        queue<int> q;
        
        // 初始化：处理初始拥有的盒子
        for (int box : initialBoxes) {
            has[box] = true;
            // 如果盒子是开的，就可以直接打开
            if (status[box] == 1) {
                ans += candies[box];
                opened[box] = true;
                q.push(box);
            }
        }
        
        // BFS遍历
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            
            // 处理当前盒子中的钥匙
            for (int key : keys[cur]) {
                status[key] = 1;  // 获得钥匙后，该盒子变为可打开
                // 如果拥有这个盒子且还没打开，就可以打开它
                if (has[key] && !opened[key]) {
                    ans += candies[key];
                    opened[key] = true;
                    q.push(key);
                }
            }
            
            // 处理当前盒子中包含的盒子
            for (int box : containedBoxes[cur]) {
                has[box] = true;  // 获得新盒子
                // 如果可以打开且还没打开，就打开它
                if (status[box] == 1 && !opened[box]) {
                    ans += candies[box];
                    opened[box] = true;
                    q.push(box);
                }
            }
        }
        
        return ans;
    }
};

class Solution2 {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, 
                   vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, 
                   vector<int>& initialBoxes) {
        unordered_set<int> canOpen;    // 当前可打开的盒子
        unordered_set<int> locked;      // 暂时锁定的盒子
        unordered_set<int> haveKey;     // 已拥有的钥匙
        
        int res = 0;
        
        // 初始化：根据初始盒子和状态分类
        for (int box : initialBoxes) {
            if (status[box]) {
                canOpen.insert(box);
            } else {
                locked.insert(box);
            }
        }
        
        // 不断处理可打开的盒子
        while (!canOpen.empty()) {
            int cur = *canOpen.begin();
            canOpen.erase(canOpen.begin());
            
            // 拿糖果
            res += candies[cur];
            
            // 处理钥匙
            for (int key : keys[cur]) {
                haveKey.insert(key);
                // 如果有锁着的盒子现在有钥匙了，就可以打开
                if (locked.count(key)) {
                    canOpen.insert(key);
                    locked.erase(key);
                }
            }
            
            // 处理内含的盒子
            for (int box : containedBoxes[cur]) {
                if (status[box] || haveKey.count(box)) {
                    canOpen.insert(box);
                } else {
                    locked.insert(box);
                }
            }
        }
        
        return res;
    }
};