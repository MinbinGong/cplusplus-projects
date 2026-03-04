/*
 * 1570. Dot Product of Two Sparse Vectors
 * 
 * Given two sparse vectors, compute their dot product.
 * 
 * Implement class SparseVector:
 * SparseVector(nums) Initializes the object with the vector nums
 * dotProduct(vec) Compute the dot product between the instance of SparseVector and vec
 * A sparse vector is a vector that has mostly zero values, you should store the sparse vector efficiently and compute the dot product between two SparseVector.
 * 
 * Follow up: What if only one of the vectors is sparse?
 * 
 * Example 1:
 * Input: nums1 = [1,0,0,2,3], nums2 = [0,3,0,4,0]
 * Output: 8
 * Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
 * v1.dotProduct(v2) = 1*0 + 0*3 + 0*0 + 2*4 + 3*0 = 8
 * 
 * Example 2:
 * Input: nums1 = [0,1,0,0,0], nums2 = [0,0,0,0,2]
 * Output: 0
 * Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
 * v1.dotProduct(v2) = 0*0 + 1*0 + 0*0 + 0*0 + 0*2 = 0
 * 
 * Example 3:
 * Input: nums1 = [0,1,0,0,2,0,0], nums2 = [1,0,0,0,3,0,4]
 * Output: 6
 * 
 * Constraints:
 * n == nums1.length == nums2.length
 * 1 <= n <= 10^5
 * 0 <= nums1[i], nums2[i] <= 100
 * 
 */
#include <vector>
using namespace std;

class SparseVector {
public:
    // 存储非零元素的 (index, value) 对
    vector<pair<int, int>> data;
    
    SparseVector(vector<int> &nums) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                data.push_back({i, nums[i]});
            }
        }
    }
    
    // 返回两个稀疏向量的点积
    int dotProduct(SparseVector& vec) {
        int res = 0;
        int i = 0, j = 0;
        auto& data1 = data;
        auto& data2 = vec.data;
        
        // 双指针遍历两个非零元素列表
        while (i < data1.size() && j < data2.size()) {
            if (data1[i].first == data2[j].first) {
                // 索引相同，相乘并累加
                res += data1[i].second * data2[j].second;
                i++;
                j++;
            } else if (data1[i].first < data2[j].first) {
                i++; // 移动索引较小的指针
            } else {
                j++;
            }
        }
        return res;
    }
};

// 使用方式：
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);
