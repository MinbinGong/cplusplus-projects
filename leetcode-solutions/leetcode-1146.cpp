/**
 * 1146. Snapshot Array
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * Implement a SnapshotArray that supports the following interface:
 * 
 * SnapshotArray(int length) initializes an array-like data structure with the given length. Initially, each element equals 0.
 * void set(index, val) sets the element at the given index to be equal to val.
 * int snap() takes a snapshot of the array and returns the snap_id: the total number of times we called snap() minus 1.
 * int get(index, snap_id) returns the value at the given index, at the time we took the snapshot with the given snap_id
 * 
 * Example 1:
 * Input: ["SnapshotArray","set","snap","set","get"]
 * [[3],[0,5],[],[0,6],[0,0]]
 * Output: [null,null,0,null,5]
 * Explanation: 
 * SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
 * 
 * Example 2:
 * Input: ["SnapshotArray","set","snap","set","get"]
 * [[3],[0,5],[],[0,6],[0,0]]
 * Output: [null,null,0,null,5]
 * Explanation: 
 * SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
 * 
 * Example 3:
 * Input: ["SnapshotArray","set","snap","set","get"]
 * [[3],[0,5],[],[0,6],[0,0]]
 * Output: [null,null,0,null,5]
 * Explanation: 
 * SnapshotArray snapshotArr = new SnapshotArray(3); // set the length to be 3
 * 
 * Note:
 * 1 <= length <= 50000
 * At most 50000 calls will be made to set, snap, and get.
 * 0 <= index < length
 * 0 <= snap_id < (the total number of times we call snap())
 * 0 <= val <= 10^9
 */
#include <vector>
#include <algorithm>
using namespace std;

class SnapshotArray {
private:
    vector<vector<pair<int, int>>> history; // 每个元素的历史修改记录 (snap_id, value)
    int cur_snap;                            // 当前快照编号

public:
    SnapshotArray(int length) {
        history.resize(length);
        cur_snap = 0;
    }
    
    void set(int index, int val) {
        auto &record = history[index];
        // 如果最后一次修改就在当前快照中，直接更新值（节省空间）
        if (!record.empty() && record.back().first == cur_snap) {
            record.back().second = val;
        } else {
            record.emplace_back(cur_snap, val);
        }
    }
    
    int snap() {
        return cur_snap++; // 返回当前编号，并递增
    }
    
    int get(int index, int snap_id) {
        auto &record = history[index];
        // 二分查找最后一个不大于 snap_id 的记录
        auto it = upper_bound(record.begin(), record.end(), make_pair(snap_id, INT_MAX));
        if (it == record.begin()) return 0; // 没有修改记录，值为默认 0
        --it;
        return it->second;
    }
};