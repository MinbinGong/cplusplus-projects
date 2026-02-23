/*
 * My Calendar I
 *
 * Implement a MyCalendar class to store your events. A new event can be added if adding the event will not cause a double booking.
 * 
 * Your class will have the method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.
 * 
 * A double booking happens when two events have some non-empty intersection (ie., there is some time that is common to both events.)
 * 
 * For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a double booking. Otherwise, return false and do not add the event to the calendar.
 * 
 * Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)
 * 
 * Note:
 * 1. The number of calls to MyCalendar.book per test case will be at most 1000.
 * 2. In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].
 * 3. The number of calls to MyCalendar.book per test case will be at most 1000.
 * 4. In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].
 * 
 */
#include <map>
using namespace std;

class MyCalendar {
private:
    map<int, int> bookings; // key: start, value: end

public:
    MyCalendar() {}

    bool book(int start, int end) {
        // Find the first booking that starts at or after 'start'
        auto it = bookings.upper_bound(start);
        
        // Check the previous booking (the one with largest start < 'start')
        if (it != bookings.begin()) {
            auto prev = it;
            --prev;
            if (prev->second > start) { // Overlaps with previous
                return false;
            }
        }
        
        // Check the next booking (the one with start > 'start')
        if (it != bookings.end()) {
            if (it->first < end) { // Overlaps with next
                return false;
            }
        }
        
        // No overlap, insert the new interval
        bookings[start] = end;
        return true;
    }
};