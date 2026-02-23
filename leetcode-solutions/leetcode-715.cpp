/*
 * Range Module
 *
 * A Range Module is a module that tracks ranges of numbers. Design a data structure to track the ranges represented as half-open intervals and query about them.
 * 
 * Implement the RangeModule class:
 * 
 * RangeModule() Initializes the object of the data structure.
 * void addRange(int left, int right) Adds the half-open interval [left, right), tracking every real number in that interval. Adding an interval that partially overlaps with currently tracked numbers should add any numbers in the interval [left, right) that are not already tracked.
 * boolean queryRange(int left, int right) Returns true if every real number in the interval [left, right) is currently being tracked, and false otherwise.
 * void removeRange(int left, int right) Stops tracking every real number currently being tracked in the half-open interval [left, right).
 * 
 * Note:
 * 1. 0 <= left < right <= 10^9.
 * 2. At most 10^4 calls will be made to addRange, queryRange, and removeRange.
 * 
 */
#include <map>
using namespace std;

class RangeModule {
private:
    // Stores disjoint half-open intervals [left, right) sorted by left.
    map<int, int> intervals;

public:
    RangeModule() {}

    // Adds a range [left, right), merging with any overlapping or adjacent intervals.
    void addRange(int left, int right) {
        // Find the first interval with left >= the new left.
        auto it = intervals.lower_bound(left);

        // Check the interval just before 'it' (if any) for overlap or adjacency.
        if (it != intervals.begin()) {
            auto prev = it;
            --prev;
            if (prev->second >= left) {  // Overlaps or touches the new range.
                left = prev->first;          // Extend left boundary.
                right = max(right, prev->second); // Extend right boundary.
                intervals.erase(prev);        // Remove the merged interval.
            }
        }

        // Merge all intervals that start at or before the new right.
        while (it != intervals.end() && it->first <= right) {
            right = max(right, it->second);
            it = intervals.erase(it);
        }

        // Insert the merged interval.
        intervals[left] = right;
    }

    // Returns true if the whole range [left, right) is covered by some interval.
    bool queryRange(int left, int right) {
        // Find the first interval with left > query left.
        auto it = intervals.upper_bound(left);
        if (it == intervals.begin()) return false; // No interval starts before or at left.
        --it; // Move to the interval with largest left <= query left.
        return it->second >= right; // Check if it covers to at least right.
    }

    // Removes the range [left, right), splitting intervals if necessary.
    void removeRange(int left, int right) {
        // Find the first interval with left >= query left.
        auto it = intervals.lower_bound(left);

        // Check the previous interval if it overlaps the removal range.
        if (it != intervals.begin()) {
            auto prev = it;
            --prev;
            if (prev->second > left) { // Overlaps (strict > because equality means no overlap)
                int old_left = prev->first;
                int old_right = prev->second;
                intervals.erase(prev);
                // Keep the part before left, if any.
                if (old_left < left) {
                    intervals[old_left] = left;
                }
                // Keep the part after right, if any.
                if (old_right > right) {
                    intervals[right] = old_right;
                }
            }
        }

        // Remove or truncate intervals that start inside [left, right).
        while (it != intervals.end() && it->first < right) {
            if (it->second <= right) {
                // Fully inside removal range → erase entirely.
                it = intervals.erase(it);
            } else {
                // Partially overlapping on the right side → keep the right part.
                intervals[right] = it->second;
                intervals.erase(it);
                break; // No further intervals can start before right.
            }
        }
    }
};