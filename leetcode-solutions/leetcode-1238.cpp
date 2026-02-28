/*
 * 1238. Circular Permutation in Binary Representation
 *
 * Given 2 integers n and start. Your task is return any permutation p of (0,1,2.....,2^n -1) such that :
 *
 * p[0] = start
 * p[i] and p[i+1] differ by only one bit in their binary representation.
 * p[0] and p[2^n -1] must also differ by only one bit in their binary representation.
 * 
 * Example 1:
 * 
 * Input: n = 2, start = 3
 * Output: [3,2,0,1]
 * Explanation: The binary representation of the permutation is (11,10,00,01). 
 * All the adjacent element differ by one bit. Another valid permutation is [3,1,0,2]
 * 
 * Example 2:
 * 
 * Input: n = 3, start = 2
 * Output: [2,6,7,5,4,0,1,3]
 * Explanation: The binary representation of the permutation is (010,110,111,101,100,000,001,011).
 * All the adjacent element differ by one bit. Another valid permutation is [2,6,7,5,4,0,1,3]
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    // 方法1：使用格雷码公式（最优解）
    // 格雷码公式：G(i) = i ^ (i >> 1)
    // 要生成以start开始的循环格雷码：result[i] = G(i) ^ start
    vector<int> circularPermutation(int n, int start) {
        int size = 1 << n;  // 2^n
        vector<int> result(size);
        
        for (int i = 0; i < size; ++i) {
            // 生成标准格雷码，然后异或start得到以start开始的序列
            int gray = i ^ (i >> 1);
            result[i] = gray ^ start;
        }
        
        return result;
    }
    
    // 方法2：先生成标准格雷码，然后旋转到start位置
    vector<int> circularPermutation2(int n, int start) {
        int size = 1 << n;
        vector<int> gray(size);
        
        // 生成标准格雷码
        for (int i = 0; i < size; ++i) {
            gray[i] = i ^ (i >> 1);
        }
        
        // 找到start在格雷码中的位置
        int startIndex = 0;
        for (int i = 0; i < size; ++i) {
            if (gray[i] == start) {
                startIndex = i;
                break;
            }
        }
        
        // 旋转数组，使start成为第一个元素
        vector<int> result(size);
        for (int i = 0; i < size; ++i) {
            result[i] = gray[(startIndex + i) % size];
        }
        
        return result;
    }
    
    // 方法3：递归生成格雷码（镜像法）
    vector<int> circularPermutation3(int n, int start) {
        // 递归生成标准格雷码
        vector<int> gray = generateGrayCode(n);
        
        // 找到start的位置并旋转
        int size = gray.size();
        int startIndex = 0;
        for (int i = 0; i < size; ++i) {
            if (gray[i] == start) {
                startIndex = i;
                break;
            }
        }
        
        vector<int> result(size);
        for (int i = 0; i < size; ++i) {
            result[i] = gray[(startIndex + i) % size];
        }
        
        return result;
    }
    
private:
    // 递归生成n位格雷码
    vector<int> generateGrayCode(int n) {
        if (n == 0) return {0};
        
        // 生成n-1位格雷码
        vector<int> prev = generateGrayCode(n - 1);
        vector<int> result;
        
        // 前半部分：0 + prev
        for (int num : prev) {
            result.push_back(num);
        }
        
        // 后半部分：1 + prev的逆序
        int add = 1 << (n - 1);
        for (int i = prev.size() - 1; i >= 0; --i) {
            result.push_back(prev[i] + add);
        }
        
        return result;
    }
    
    // 方法4：迭代生成格雷码
    vector<int> circularPermutation4(int n, int start) {
        int size = 1 << n;
        vector<int> gray(size, 0);
        
        // 迭代生成格雷码
        for (int i = 1; i < size; ++i) {
            // 计算最低有效位变化的位置
            // 公式：gray[i] = gray[i-1] ^ (i & -i)
            gray[i] = gray[i-1] ^ (i & -i);
        }
        
        // 找到start的位置并旋转
        int startIndex = 0;
        for (int i = 0; i < size; ++i) {
            if (gray[i] == start) {
                startIndex = i;
                break;
            }
        }
        
        vector<int> result(size);
        for (int i = 0; i < size; ++i) {
            result[i] = gray[(startIndex + i) % size];
        }
        
        return result;
    }
};

// 方法5：使用位运算直接生成（另一种公式）
class Solution5 {
public:
    vector<int> circularPermutation(int n, int start) {
        int size = 1 << n;
        vector<int> result(size);
        
        // 直接生成：result[i] = start ^ i ^ (i >> 1)
        // 这等价于：result[i] = (i ^ (i >> 1)) ^ start
        for (int i = 0; i < size; ++i) {
            result[i] = start ^ i ^ (i >> 1);
        }
        
        return result;
    }
};

// 测试用例示例：
// 输入: n = 2, start = 3
// 输出: [3,2,0,1] 或 [3,1,0,2] 等有效排列
// 解释: 
// 二进制表示: 3(11), 2(10), 0(00), 1(01)
// 相邻数字只有一位不同，首尾3和1也只有一位不同
//
// 输入: n = 3, start = 2
// 可能的输出: [2,3,1,0,4,5,7,6]
// 验证: 相邻数字二进制只有一位不同

// 复杂度分析：
// 方法1（格雷码公式）：
// - 时间复杂度：O(2^n)，需要生成2^n个数字
// - 空间复杂度：O(2^n)，存储结果数组
//
// 方法2（旋转法）：
// - 时间复杂度：O(2^n)，生成格雷码O(2^n)，查找start位置O(2^n)，旋转O(2^n)
// - 空间复杂度：O(2^n)，需要额外存储标准格雷码
//
// 方法3（递归法）：
// - 时间复杂度：O(2^n)，递归生成格雷码
// - 空间复杂度：O(2^n)，递归栈深度O(n)，结果数组O(2^n)
//
// 方法4（迭代法）：
// - 时间复杂度：O(2^n)
// - 空间复杂度：O(2^n)

// 推荐使用方法1，代码最简洁，效率最高，且不需要额外查找start位置。