/*
 * 1090. Largest Values From Labels
 *
 * We have a set of items: the i-th item has value values[i] and label labels[i].
 * Then, we choose a subset S of these items, such that:
 * |S| <= num_wanted
 * For every label L, the number of items in S with label L is <= use_limit.
 * Return the largest possible sum of the subset S.
 * 
 * Example 1:
 * Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], num_wanted = 3, use_limit = 1
 * Output: 9
 * Explanation: The subset chosen is the first, third, and fifth item.
 * 
 * Example 2:
 * Input: values = [5,4,3,2,1], labels = [1,3,3,3,2], num_wanted = 3, use_limit = 2
 * Output: 12
 * Explanation: The subset chosen is the first, second, and third item.
 * 
 * Example 3:
 * Input: values = [9,8,8,7,6], labels = [0,0,0,1,1], num_wanted = 3, use_limit = 1
 * Output: 16
 * Explanation: The subset chosen is the first and fourth item.
 * 
 * Note:
 * 1 <= values.length == labels.length <= 20000
 * 0 <= values[i], labels[i] <= 20000
 * 1 <= num_wanted, use_limit <= values.length
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {
        int n = values.size();
        // 1. 将值和标签配对
        vector<pair<int, int>> items;
        for (int i = 0; i < n; ++i) {
            items.emplace_back(values[i], labels[i]);
        }

        // 2. 按值降序排序
        sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });

        unordered_map<int, int> labelCount; // 记录每个标签已选数量
        int ans = 0;
        int selected = 0; // 记录已选元素个数

        // 3. 贪心选择
        for (const auto& [value, label] : items) {
            if (selected >= numWanted) break; // 达到总数上限，提前结束
            if (labelCount[label] < useLimit) { // 标签数量未达上限
                labelCount[label]++;
                selected++;
                ans += value;
            }
        }

        return ans;
    }
};