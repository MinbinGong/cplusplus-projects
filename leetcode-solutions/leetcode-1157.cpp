/**
 * 1157. Online Majority Element In Subarray
 * Hard
 * 
 * (This problem is an interactive problem.)
 * 
 * Implementing the class MajorityChecker, which has the following API:
 * 
 * MajorityChecker(int[] arr) constructs an instance of MajorityChecker with the given array arr;
 * int query(int left, int right, int threshold) has arguments such that:
 * 0 <= left <= right < arr.length representing a subarray of arr;
 * 2 * threshold > right - left + 1, ie. the threshold is always a strict majority of the length of the subarray
 * Each query(...) returns the element in arr[left], arr[left+1], ..., arr[right] that occurs at least threshold times, or -1 if no such element exists.
 * 
 * Example:
 * MajorityChecker majorityChecker = new MajorityChecker([1,1,2,2,1,1]);
 * majorityChecker.query(0,5,4); // returns 1
 * majorityChecker.query(0,3,3); // returns -1
 * 
 * Note:
 * 1 <= arr.length <= 20000
 * 1 <= arr[i] <= 20000
 * For each query, 0 <= left <= right < len(arr)
 * For each query, 2 * threshold > right - left + 1
 * The number of queries is at most 10000
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class MajorityChecker {
    vector<int> arr;           // original array
    vector<int> comp;          // compressed values (0..M-1)
    vector<int> orig;          // map compressed index to original value
    vector<int> timestamp;     // last query id for each compressed value
    vector<int> freq;          // current frequency for each compressed value
    int cur;                   // current query id

public:
    MajorityChecker(vector<int>& arr) : arr(arr) {
        unordered_map<int, int> valToIdx;
        int idx = 0;
        for (int x : arr) {
            if (valToIdx.find(x) == valToIdx.end()) {
                valToIdx[x] = idx++;
                orig.push_back(x);
            }
            comp.push_back(valToIdx[x]);
        }
        int M = idx;
        timestamp.assign(M, 0);
        freq.assign(M, 0);
        cur = 0;
    }

    int query(int left, int right, int threshold) {
        ++cur;  // new query id
        for (int i = left; i <= right; ++i) {
            int v = comp[i];
            if (timestamp[v] != cur) {
                timestamp[v] = cur;
                freq[v] = 1;
            } else {
                ++freq[v];
            }
            if (freq[v] >= threshold) {
                return orig[v];
            }
        }
        return -1;
    }
};