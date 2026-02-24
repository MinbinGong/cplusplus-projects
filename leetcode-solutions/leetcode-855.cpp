/*
 * 855. Exam Room
 * 
 * In an exam room, there are N seats in a single row, numbered 0, 1, 2, ..., N-1.
 * 
 * When a student enters the room, they must sit in the seat that maximizes the distance to the closest person.  If there are multiple such seats, they sit in the seat with the lowest number.  (Also, if no one is in the room, then the student sits at seat number 0.)
 * 
 * Return a class ExamRoom(int N) that exposes two functions: ExamRoom.seat() returning an int representing what seat the student sat in, and ExamRoom.leave(int p) representing that the student in seat number p now leaves the room.  It is guaranteed that any calls to ExamRoom.leave(p) have a student sitting in seat p.
 * 
 * Example 1:
 * Input: ["ExamRoom","seat","seat","seat","seat","leave","seat"], [[10],[],[],[],[],[4],[]]
 * Output: [null,0,9,4,2,null,5]
 * Explanation:
 * ExamRoom(10) -> null
 * seat() -> 0, no one is in the room, then the student sits at seat number 0.
 * seat() -> 9, the student sits at the last seat number 9.
 * seat() -> 4, the student sits at the last seat number 4.
 * seat() -> 2, the student sits at the last seat number 2.
 * leave(4) -> null
 * seat() -> 5, the student​​​​​​​ sits at the last seat number 5.
 * 
 * ​​​​​​​Note:
 * 1 <= N <= 10^9
 * ExamRoom.seat() and ExamRoom.leave() will be called at most 10^4 times across all test cases.
 * Calls to ExamRoom.leave(p) are guaranteed to have a student currently sitting in seat number p.
 */
#include <set>
#include <map>
using namespace std;

class ExamRoom {
private:
    int N;
    // 区间按[距离]排序，距离相同按左端点小优先
    set<pair<int, int>> intervals;
    // 左右端点映射，用于快速查找相邻区间
    map<int, int> leftMap;  // 右端点 -> 左端点
    map<int, int> rightMap; // 左端点 -> 右端点
    
    // 计算区间长度（优先级标准）
    int getDistance(int l, int r) {
        if (l == -1) return r;          // 左边界区间
        if (r == N) return N - 1 - l;    // 右边界区间
        return (r - l) / 2;              // 中间区间
    }
    
    // 添加新区间
    void addInterval(int l, int r) {
        intervals.insert({l, r});
        leftMap[r] = l;
        rightMap[l] = r;
    }
    
    // 删除区间
    void removeInterval(int l, int r) {
        intervals.erase({l, r});
        leftMap.erase(r);
        rightMap.erase(l);
    }
    
public:
    ExamRoom(int n) {
        N = n;
        // 初始整个区间
        addInterval(-1, N);
    }
    
    int seat() {
        // 找到最优区间（最后一个元素是距离最大的）
        auto best = *intervals.rbegin();
        int l = best.first, r = best.second;
        
        int pos;
        if (l == -1) {
            pos = 0;
        } else if (r == N) {
            pos = N - 1;
        } else {
            pos = l + (r - l) / 2;
        }
        
        // 移除原区间，添加两个新区间
        removeInterval(l, r);
        addInterval(l, pos);
        addInterval(pos, r);
        
        return pos;
    }
    
    void leave(int p) {
        // 找到左右相邻区间
        int l = leftMap[p];   // 区间 [l, p]
        int r = rightMap[p];  // 区间 [p, r]
        
        // 移除两个小区间
        removeInterval(l, p);
        removeInterval(p, r);
        // 合并成大区间
        addInterval(l, r);
    }
};