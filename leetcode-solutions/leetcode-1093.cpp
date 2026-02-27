/*
 * 1093. Statistics from a Large Sample
 *
 * We sampled integers between 0 and 255, and stored the results in an array count:  count[k] is the number of integers we sampled equal to k.
 * Return the minimum, maximum, mean, median, and mode of the sample respectively, as an array of floating point numbers.
 * The mode is guaranteed to be unique.
 * (Recall that the median of a sample is:
 * The middle element, if the elements of the sample were sorted and the number of elements is odd;
 * The average of the middle two elements, if the elements of the sample were sorted and the number of elements is even.)
 * 
 * Note:
 * 1 <= count.length == 256
 * 1 <= count[i] <= 10^9
 * The array count is a representation of the distribution of the sample.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        int n = count.size();
        long long total = 0;          // 样本总数
        long long sum = 0;             // 样本值的总和
        int min_val = -1, max_val = -1;
        int mode_val = 0, max_count = 0;

        // 第一遍遍历，计算总和、总数、最小值、最大值、众数
        for (int i = 0; i < n; ++i) {
            if (count[i] > 0) {
                total += count[i];
                sum += (long long)i * count[i];
                if (min_val == -1) min_val = i;
                max_val = i;
                if (count[i] > max_count) {
                    max_count = count[i];
                    mode_val = i;
                }
            }
        }

        double mean = (double)sum / total;

        // 计算中位数
        double median = 0.0;
        int cnt = 0;
        // 找到第 (total+1)/2 个数（即中位数的第一个位置，如果是奇数则是中位数本身，偶数则是左中位数）
        int pos1 = (total + 1) / 2;          // 例如 total=4，pos1=2；total=5，pos1=3
        int pos2 = (total + 2) / 2;          // 如果是偶数，需要第二个位置：total/2 + 1，即 (total+2)/2
        int left = -1, right = -1;

        for (int i = 0; i < n; ++i) {
            if (count[i] > 0) {
                cnt += count[i];
                if (left == -1 && cnt >= pos1) {
                    left = i;
                }
                if (right == -1 && cnt >= pos2) {
                    right = i;
                    break;
                }
            }
        }

        if (total % 2 == 1) {
            median = left;          // 奇数时 left 就是中位数
        } else {
            median = (left + right) / 2.0;
        }

        return { (double)min_val, (double)max_val, mean, median, (double)mode_val };
    }
};