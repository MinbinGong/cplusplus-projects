/*
 * My Calendar II
 *
 * Implement a MyCalendarTwo class to store your events. A new event can be added if adding the event will not cause a triple booking.
 * 
 * Your class will have the method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.
 * 
 * A triple booking happens when three events have some non-empty intersection (ie., there is some time that is common to all 3 events.)
 * 
 * For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a triple booking. Otherwise, return false and do not add the event to the calendar.
 * 
 * Your class will be called like this: MyCalendarTwo cal = new MyCalendarTwo(); MyCalendarTwo.book(start, end)
 * 
 * Note:
 * 1. The number of calls to MyCalendarTwo.book per test case will be at most 1000.
 * 2. In calls to MyCalendarTwo.book(start, end), start and end are integers in the range [0, 10^9].
 * 
 */
#include <vector>
using namespace std;

class MyCalendarTwo {
private:
    vector<pair<int, int>> single;   // intervals booked once
    vector<pair<int, int>> double_;  // intervals booked twice (overlaps)

public:
    MyCalendarTwo() {}

    bool book(int start, int end) {
        // Check for triple booking: does [start, end) intersect any double-booked interval?
        for (const auto& [dStart, dEnd] : double_) {
            if (max(start, dStart) < min(end, dEnd)) {
                return false;   // would cause triple booking
            }
        }

        // Find overlaps with single bookings and add them to double_
        for (const auto& [sStart, sEnd] : single) {
            int overlapStart = max(start, sStart);
            int overlapEnd = min(end, sEnd);
            if (overlapStart < overlapEnd) {
                double_.emplace_back(overlapStart, overlapEnd);
            }
        }

        // Finally, book the new interval as a single booking
        single.emplace_back(start, end);
        return true;
    }
};
