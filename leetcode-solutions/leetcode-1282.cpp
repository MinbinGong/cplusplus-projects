/**
 * 1282. Group the People Given the Group Size They Belong To
 * 
 * There are n people that are split into some unknown number of groups. Each person is labeled with a unique ID from 0 to n - 1.
 * 
 * You are given an integer array groupSizes, where groupSizes[i] is the size of the group that person i is in. For example, if groupSizes[1] = 3, then person 1 must be in a group of size 3.
 * 
 * Return a list of groups such that each person i is in a group of size groupSizes[i].
 * 
 * Each person should appear in exactly one group, and every person must be in a group. If there are multiple answers, return any of them. It is guaranteed that there will be at least one valid solution for the given input.
 * 
 * Example 1:
 * Input: groupSizes = [3,3,3,3,3,1,3]
 * Output: [[5],[0,1,2],[3,4,6]]
 * Explanation: 
 * Person 0 must be in a group of size 3.
 * Person 1 must be in a group of size 3.
 * Person 2 must be in a group of size 3.
 * Person 3 must be in a group of size 3.
 * Person 4 must be in a group of size 3.
 * Person 5 must be in a group of size 1.
 * Person 6 must be in a group of size 3.
 * 
 * Example 2:
 * Input: groupSizes = [2,1,3,3,3,2]
 * Output: [[1],[0,5],[2,3,4]]
 * Explanation: 
 * Person 0 must be in a group of size 2.
 * Person 1 must be in a group of size 1.
 * Person 2 must be in a group of size 3.
 * Person 3 must be in a group of size 3.
 * Person 4 must be in a group of size 3.
 * Person 5 must be in a group of size 2.
 * Person 6 must be in a group of size 2.
 * 
 * Note:
 * 1 <= n <= 500
 * 1 <= groupSizes[i] <= n
 * 
 */
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        unordered_map<int, vector<int>> temp;   // 组大小 -> 人员索引列表
        vector<vector<int>> result;
        
        for (int i = 0; i < groupSizes.size(); ++i) {
            int size = groupSizes[i];
            temp[size].push_back(i);
            // 当当前大小的组人数达到 size 时，就形成一个完整的分组
            if (temp[size].size() == size) {
                result.push_back(temp[size]);
                temp[size].clear();   // 清空，准备下一组
            }
        }
        
        return result;
    }
};