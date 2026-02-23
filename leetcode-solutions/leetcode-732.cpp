/*
 * My Calendar III
 *
 * Implement a MyCalendarThree class to store your events. A new event can always be added.
 * 
 * Your class will have the method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.
 * 
 * A K-booking happens when K events have some non-empty intersection (ie., there is some time that is common to all K events.)
 * 
 * For each call to the method MyCalendar.book, return an integer K representing the largest integer such that there exists a K-booking in the calendar.
 * 
 * Your class will be called like this: MyCalendarThree cal = new MyCalendarThree(); MyCalendarThree.book(start, end)
 * 
 * Note:
 * 1. The number of calls to MyCalendarThree.book per test case will be at most 400.
 * 2. In calls to MyCalendarThree.book(start, end), start and end are integers in the range [0, 10^9].
 * 
 */
#include <map>
#include <algorithm>
using namespace std;

class MyCalendarThree {
private:
    map<int, int> diff; // difference array: +1 at start, -1 at end
public:
    MyCalendarThree() {}
    
    int book(int start, int end) {
        // record the event
        diff[start]++;
        diff[end]--;
        
        int active = 0, maxActive = 0;
        // sweep through the timeline in order
        for (auto& [time, change] : diff) {
            active += change;
            maxActive = max(maxActive, active);
        }
        return maxActive;
    }
};