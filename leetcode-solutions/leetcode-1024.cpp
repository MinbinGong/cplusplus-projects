/*
 * 1024. Video Stitching
 *
 * You are given a series of video clips from a sporting event that lasted T seconds.  These video clips can be overlapping with each other and have varied lengths.
 *
 * Each video clip clips[i] is an interval: it starts at time clips[i][0] and ends at time clips[i][1].  We can cut these clips into segments freely: for example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].
 *
 * Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event ([0, T]).  If the task is impossible, return -1.
 *
 * Example 1:
 *
 * Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
 * Output: 3
 * Explanation: 
 * We can cut the event into segments [0, 2], [4, 6], [8, 10].
 * 
 * Example 2:
 *
 * Input: clips = [[0,1],[1,2]], T = 5
 * Output: -1
 * Explanation: 
 * We can't cover [0,5] with only [0,1] and [0,2].
 * 
 * Note:
 * 
 * 1 <= clips.length <= 100
 * 0 <= clips[i][0], clips[i][1] <= 100
 * 0 <= T <= 100
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        // sort by start time, then by end time descending
        sort(clips.begin(), clips.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[0] == b[0]) return a[1] > b[1];
                 return a[0] < b[0];
             });

        int end = 0;         // current covered end
        int i = 0;           // index in clips
        int count = 0;
        int n = clips.size();

        while (end < T) {
            int maxEnd = end;
            // pick the clip with start <= current end that gives the furthest end
            while (i < n && clips[i][0] <= end) {
                maxEnd = max(maxEnd, clips[i][1]);
                ++i;
            }
            if (maxEnd == end) { // no progress
                return -1;
            }
            end = maxEnd;
            ++count;
        }
        return count;
    }
};