/*
 * Sliding Window Median
 *
 * Given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
 * 
 * Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.
 * 
 * Constraints:
 * 1 <= nums.length <= 105
 * -231 <= nums[i] <= 231 - 1
 * 1 <= k <= nums.length
 * 
 */
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        multiset<int> low, high;   // low stores smaller half, high larger half

        // Initialize with first k elements
        for (int i = 0; i < k; ++i) {
            low.insert(nums[i]);
        }
        // Move the largest k/2 elements to high to balance
        for (int i = 0; i < k / 2; ++i) {
            high.insert(*low.rbegin());
            low.erase(prev(low.end()));
        }

        // First median
        if (k % 2) {
            res.push_back(*low.rbegin());
        } else {
            res.push_back(((double)*low.rbegin() + (double)*high.begin()) / 2.0);
        }

        for (int i = k; i < nums.size(); ++i) {
            int outgoing = nums[i - k];
            int incoming = nums[i];

            // Remove outgoing element
            auto it = low.find(outgoing);
            if (it != low.end()) {
                low.erase(it);
            } else {
                it = high.find(outgoing);
                high.erase(it);
            }

            // Insert incoming element
            if (low.empty() || incoming <= *low.rbegin()) {
                low.insert(incoming);
            } else {
                high.insert(incoming);
            }

            // Rebalance
            if (low.size() > high.size() + 1) {
                high.insert(*low.rbegin());
                low.erase(prev(low.end()));
            } else if (high.size() > low.size()) {
                low.insert(*high.begin());
                high.erase(high.begin());
            }

            // Current median
            if (k % 2) {
                res.push_back(*low.rbegin());
            } else {
                res.push_back(((double)*low.rbegin() + (double)*high.begin()) / 2.0);
            }
        }
        return res;
    }
};