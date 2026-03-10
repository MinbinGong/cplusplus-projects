/**
 * 1739. Building Boxes
 * 
 * You have a cubic storeroom where the width, length, and height of the room are all equal to n units. You are asked to place n boxes in this room where each box is a cube of unit side length. There are however some rules to placing the boxes:
 * You can place the boxes anywhere on the floor.
 * If box x is placed on top of the box y, then each side of the four vertical sides of the box y must either be adjacent to another box or to a wall.
 * Given an integer n, return the minimum possible number of boxes touching the floor.
 * 
 * Example 1:
 * Input: n = 3
 * Output: 3
 * Explanation: The figure above is for the placement of the three boxes.
 * These boxes are placed in the corner of the room, where the corner is on the left side.
 * 
 * Example 2:
 * Input: n = 4
 * Output: 3
 * Explanation: The figure above is for the placement of the four boxes.
 * 
 * Constraints:
 * 1 <= n <= 109
 */
#include <iostream>
using namespace std;

class Solution {
public:
    int minimumBoxes(int n) {
        // 使用 long long 防止计算过程中溢出（n 最大为 1e9）
        long long total = 0; // 当前已放置的盒子总数
        long long layer = 1;  // 当前层的序号（从1开始）
        long long bottom = 0; // 当前接触地面的盒子总数

        // 第一阶段：堆放完整的阶梯层
        // 第 layer 层如果摆满，可以放 layer*(layer+1)/2 个盒子，
        // 同时这一整层需要新增 layer 个接触地面的盒子
        while (total + layer * (layer + 1) / 2 <= n) {
            total += layer * (layer + 1) / 2; // 加上这一层所有的盒子
            bottom += layer;                  // 这一层的底部盒子数
            layer++;                           // 尝试下一层
        }

        // 第二阶段：处理剩余的盒子
        // 剩余盒子需要从最底层开始，每次增加一个底部盒子，
        // 这个底部盒子能往上堆叠 k 个盒子（k 从 1 开始递增）
        long long k = 1;
        while (total < n) {
            total += k;    // 新放的底部盒子及其上方能堆的数量
            bottom += 1;   // 增加一个底部盒子
            k++;           // 下一次可以多堆一个
        }

        return bottom;
    }
};