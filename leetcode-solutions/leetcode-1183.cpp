/*
 * 1183. Maximum Number of Ones
 * 
 * Consider a matrix M with dimensions width * height, such that every cell has value 0 or 1, and any square sub-matrix of M of size sideLength * sideLength has at most maxOnes ones.
 * 
 * Return the maximum possible number of ones that the matrix M can have.
 * 
 * Example 1:
 * Input: width = 3, height = 3, sideLength = 2, maxOnes = 1
 * Output: 4
 * Explanation: 
 * In a 3*3 matrix, no 2*2 sub-matrix can have more than 1 one.
 * The best solution that has 4 ones is:
 * [1,0,1]
 * [0,0,0]
 * [1,0,1]
 * 
 * Example 2:
 * Input: width = 3, height = 3, sideLength = 2, maxOnes = 2
 * Output: 6
 * Explanation: 
 * [1,0,1]
 * [1,0,1]
 * 
 * Note:
 * 1 <= width, height <= 100
 * 1 <= sideLength <= width, height
 * 0 <= maxOnes <= sideLength * sideLength
 * 
 */
class Solution {
public:
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
        // 创建一个数组来统计模板中每个位置的等效出现次数
        // 模板大小为 sideLength * sideLength
        vector<int> cnt(sideLength * sideLength, 0);

        // 遍历大矩阵的每一个单元格
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                // 计算该单元格在模板中的等效位置 (r, c)
                int r = i % sideLength;
                int c = j % sideLength;
                // 将二维坐标转换为一维索引，并增加计数
                // 这个计数代表：如果在模板的 (r, c) 位置放一个 1，
                // 那么整个大矩阵中将会有多少个单元格必须为 1。
                int idx = r * sideLength + c;
                cnt[idx]++;
            }
        }

        // 为了最大化总数，我们选择出现次数最多的 maxOnes 个位置
        // 所以需要将计数数组从大到小排序
        sort(cnt.rbegin(), cnt.rend());

        // 将前 maxOnes 个最大计数相加，得到最终答案
        int ans = 0;
        for (int i = 0; i < maxOnes; ++i) {
            ans += cnt[i];
        }
        return ans;
    }
};

