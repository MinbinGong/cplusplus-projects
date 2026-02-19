/*
 * Contains Duplicate III
 * 
 * Given an integer array nums and two integers k and t, return true if there are two distinct indices i and j in the array
 * such that abs(nums[i] - nums[j]) <= t and abs(i - j) <= k.
 * 
 * Constraints:
 * 1. 1 <= nums.length <= 2 * 104
 * 2. -231 <= nums[i] <= 231 - 1
 * 3. 0 <= k <= 104
 * 4. 0 <= t <= 231 - 1
 */
#include <set>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution1 {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k <= 0 || t < 0) return false;
        
        set<long long> window; // using long long to avoid overflow
        for (int i = 0; i < nums.size(); ++i) {
            if (i > k) {
                window.erase((long long)nums[i - k - 1]);
            }
            auto it = window.lower_bound((long long)nums[i] - t);
            if (it != window.end() && *it <= (long long)nums[i] + t) {
                return true;
            }
            window.insert((long long)nums[i]);
        }
        return false;
    }
};

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k <= 0 || t < 0) return false;
        
        unordered_map<long long, long long> buckets; // bucket id -> value
        long long bucketSize = (long long)t + 1; // avoid t=0 case
        
        for (int i = 0; i < nums.size(); ++i) {
            long long num = (long long)nums[i];
            long long id = getBucketId(num, bucketSize);
            
            // Check same bucket
            if (buckets.count(id)) return true;
            
            // Check adjacent buckets
            if (buckets.count(id - 1) && num - buckets[id - 1] <= t) return true;
            if (buckets.count(id + 1) && buckets[id + 1] - num <= t) return true;
            
            // Insert into bucket
            buckets[id] = num;
            
            // Remove element that is out of window
            if (i >= k) {
                long long oldNum = (long long)nums[i - k];
                long long oldId = getBucketId(oldNum, bucketSize);
                buckets.erase(oldId);
            }
        }
        return false;
    }
    
private:
    long long getBucketId(long long num, long long bucketSize) {
        // For negative numbers, we need to shift to ensure floor division.
        // Using (num - LLONG_MIN) / bucketSize works for all values, but simpler:
        // return num >= 0 ? num / bucketSize : (num + 1) / bucketSize - 1;
        // This handles negative correctly.
        return num >= 0 ? num / bucketSize : (num + 1) / bucketSize - 1;
    }
};