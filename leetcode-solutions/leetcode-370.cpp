/*
 * Range Addition
 * 
 * You are given an integer length and an array updates where updates[i] = [startIdxi, endIdxi, inci].
 * 
 * You have an array arr of length length with all zeros, and you have some operation to apply on arr. In the ith operation, you should increment all the elements arr[startIdxi], arr[startIdxi + 1], ..., arr[endIdxi] by inci.
 * 
 * Return arr after applying all the updates.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> diff(length, 0); // 差分数组
        
        // 构建差分数组
        for (const auto& op : updates) {
            int start = op[0];
            int end = op[1];
            int inc = op[2];
            diff[start] += inc;
            if (end + 1 < length) {
                diff[end + 1] -= inc;
            }
        }
        
        // 通过前缀和还原原数组
        vector<int> result(length);
        int prefix = 0;
        for (int i = 0; i < length; ++i) {
            prefix += diff[i];
            result[i] = prefix;
        }
        return result;
    }
};