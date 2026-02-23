/*
 * Max Stack
 *
 * Design a max stack data structure that supports the stack operations and supports finding the stack's maximum element.
 * 
 * Implement the MaxStack class:
 * 
 * MaxStack() Initializes the stack object.
 * void push(int x) Pushes element x onto the stack.
 * int pop() Removes the element on top of the stack and returns it.
 * int top() Gets the element on the top of the stack without removing it.
 * int peekMax() Retrieves the maximum element in the stack without removing it.
 * int popMax() Retrieves the maximum element in the stack and removes it. If there is more than one maximum element, only remove the top-most one.
 * 
 * Note:
 * 1. -10^7 <= x <= 10^7.
 * 2. At most 10^4 calls will be made to push, pop, top, peekMax, and popMax.
 * 3. There will be at least one element in the stack when pop, top, peekMax, or popMax is called.
 * 
 */
#include <list>
#include <map>
#include <vector>

class MaxStack {
private:
    std::list<int> st;  // maintains stack order (back = top)
    // for each value, store iterators to its occurrences in the list
    // the most recent occurrence is at the back of the vector
    std::map<int, std::vector<std::list<int>::iterator>> pos;

public:
    MaxStack() {}

    void push(int x) {
        st.push_back(x);
        pos[x].push_back(std::prev(st.end()));
    }

    int pop() {
        int val = st.back();               // value of top element
        auto it = std::prev(st.end());      // iterator to top element
        st.erase(it);                       // remove from list
        pos[val].pop_back();                 // remove its iterator
        if (pos[val].empty()) {
            pos.erase(val);                  // clean up if no more occurrences
        }
        return val;
    }

    int top() {
        return st.back();
    }

    int peekMax() {
        return pos.rbegin()->first;          // largest key in map
    }

    int popMax() {
        int maxVal = pos.rbegin()->first;    // current maximum value
        auto& vec = pos[maxVal];
        auto it = vec.back();                 // iterator to most recent occurrence of maxVal
        st.erase(it);                          // remove from list
        vec.pop_back();                         // remove its iterator
        if (vec.empty()) {
            pos.erase(maxVal);                  // clean up
        }
        return maxVal;
    }
};