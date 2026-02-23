/*
 * 774. Minimize Max Distance to Gas Station
 *
 * On a horizontal number line, we have gas stations at positions stations[0], stations[1], ..., stations[N-1], where N = stations.length.
 * Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.
 * Return the smallest possible value of D.
 * 
 * Example:
 * Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
 * Output: 0.500000
 * 
 * Note:
 * 1. stations.length will be an integer in range [10, 2000].
 * 2. stations[i] will be an integer in range [0, 10^8].
 * 3. K will be an integer in range [1, 10^6].
 * 4. Answers within 10^-6 of the true value will be accepted as correct.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    double minmaxGasDist(vector<int>& stations, int K) {
        double left = 0, right = 1e8;
        // 二分查找最小化的最大距离，精度要求 1e-6
        while (right - left > 1e-6) {
            double mid = left + (right - left) / 2;
            if (check(stations, K, mid)) {
                // 如果当前 mid 可行（所需新建站数 <= K），尝试更小的值
                right = mid;
            } else {
                // 否则需要增大 mid
                left = mid;
            }
        }
        return left;
    }

private:
    // 判断能否通过最多新建 K 个加油站，使得相邻加油站的最大距离不超过 D
    bool check(vector<int>& stations, int K, double D) {
        int count = 0;
        int n = stations.size();
        for (int i = 0; i < n - 1; ++i) {
            // 区间长度
            double gap = stations[i + 1] - stations[i];
            // 需要在该区间内新建的加油站数量
            // 例如 gap=10, D=3, 需要新建 ceil(10/3)-1 = 2 个站
            if (gap > D) {
                // 这里用 (gap + D * 1e-9) / D 来避免浮点精度误差导致少算一个站
                // 等价于 ceil(gap / D) - 1
                count += static_cast<int>((gap + 1e-9) / D);
            }
        }
        return count <= K;
    }
};