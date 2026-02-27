/*
 * 1104. Path In Zigzag Labelled Binary Tree
 * 
 * In an infinite binary tree where every node has two children, the nodes are labelled in row order.
 * 
 * In the odd numbered rows (ie., the first, third, fifth,...), the labelling is left to right, while in the even numbered rows (second, fourth, sixth,...), the labelling is right to left.
 * 
 * Given the label of a node in this tree, return the labels in the path from the root of the tree to the node with that label.
 * 
 * 1 <= label <= 10^6
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        // 1. 计算label所在的深度（行数）
        int depth = 1;
        while ((1 << depth) <= label) {
            depth++;
        }
        
        vector<int> result;
        result.push_back(label);
        
        // 2. 从label向上回溯到根节点
        while (label > 1) {
            // 计算当前深度的最小值和最大值
            int levelMin = 1 << (depth - 1);
            int levelMax = (1 << depth) - 1;
            
            // 将之字形标签转换为正常标签
            int normalLabel;
            if (depth % 2 == 1) { // 奇数行：从左到右
                normalLabel = label;
            } else { // 偶数行：从右到左
                normalLabel = levelMin + (levelMax - label);
            }
            
            // 计算父节点的正常标签
            int parentNormal = normalLabel / 2;
            
            // 深度减1，进入上一层
            depth--;
            
            // 计算上一层的边界
            levelMin = 1 << (depth - 1);
            levelMax = (1 << depth) - 1;
            
            // 将父节点的正常标签转换回之字形标签
            if (depth % 2 == 1) { // 奇数行：从左到右
                label = parentNormal;
            } else { // 偶数行：从右到左
                label = levelMin + (levelMax - parentNormal);
            }
            
            result.push_back(label);
        }
        
        // 3. 反转结果，得到从根到节点的路径
        reverse(result.begin(), result.end());
        return result;
    }
};