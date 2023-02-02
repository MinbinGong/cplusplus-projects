#include <vector>
#include <queue>
#include <algorithm>

struct Interval
{
    int start = 0;
    int end = 0;
    Interval(int s = 0, int e = 0) :start(s), end(e) {}
};

int minMeetingRooms(std::vector<Interval>& intervals)
{
    std::vector<int> starts, ends;
    for (const auto& i : intervals)
    {
        starts.emplace_back(i.start);
        ends.emplace_back(i.end);
    }

    std::sort(starts.begin(), starts.end());
    std::sort(ends.begin(), ends.end());

    int min_rooms = 0, cnt_rooms = 0;
    int s = 0, e = 0;
    while (s < starts.end())
    {
        if (starts[s] < ends[0])
        {
            ++cnt_rooms;
            min_rooms = max(min_rooms, cnt_rooms);
            ++s;
        }
        else
        {
            --cnt_rooms;
            ++e;
        }
    }
    return min_rooms;
}

int minMeetingRoomsOnHeap(std::vector<Interval>& intervals)
{
    std::sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
        return a.start < b.start;
        });
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    for (auto a : intervals)
    {
        if (!q.empty()&&q.top() <= a.start)
        {
            q.pop();
        }
        q.push(a.end);
    }

    return q.size();
}