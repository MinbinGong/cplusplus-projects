/*
 * 1172. Dinner Plate Stacks
 * 
 * You have an infinite number of stacks arranged in a row and numbered (left to right) from 0, each of the stacks has the same maximum capacity.
 * 
 * Implement the DinnerPlates class:
 * 
 * DinnerPlates(int capacity) Initializes the object with the maximum capacity of the stacks.
 * void push(int val) Pushes the given positive integer val into the leftmost stack with size less than capacity.
 * int pop() Returns the value at the top of the rightmost non-empty stack and removes it from that stack, and returns -1 if all stacks are empty.
 * int popAtStack(int index) Returns the value at the top of the stack with the given index and removes it from that stack, and returns -1 if the stack with that given index is empty.
 * 
 * Example 1:
 * Input: 
 * ["DinnerPlates","push","push","push","push","push","popAtStack","push","push","popAtStack","popAtStack","pop","pop","pop","pop","pop"]
 * Output: 
 * [null,null,null,null,null,null,2,null,null,2,3,1,4,-1,-1,-1]
 * 
 * Explanation: 
 * DinnerPlates D = DinnerPlates(2);  // Initialize with capacity = 2
 * D.push(1);
 * D.push(2);
 * D.push(3);
 * D.push(4);
 * D.push(5);         // The stacks are now:  2  4
 *                                           1  3  5
 *                                           ﹈ ﹈ ﹈
 * D.popAtStack(0);   // Returns 2.  The stacks are now:     4
 *                                                       1  3  5
 *                                                       ﹈ ﹈ ﹈
 * D.push(20);        // The stacks are now: 20  4
 *                                           1  3  5
 *                                           ﹈ ﹈ ﹈
 * D.push(21);        // The stacks are now: 20  4 21
 *                                           1  3  5
 *                                           ﹈ ﹈ ﹈
 * D.popAtStack(0);   // Returns 20.  The stacks are now:     4 21
 *                                                        1  3  5
 *                                                        ﹈ ﹈ ﹈
 * D.popAtStack(2);   // Returns 21.  The stacks are now:     4
 *                                                        1  3  5
 *                                                        ﹈ ﹈ ﹈ 
 * D.pop()            // Returns 5.  The stacks are now:      4
 *                                                        1  3 
 *                                                        ﹈ ﹈  
 * D.pop()            // Returns 4.  The stacks are now:   1  3 
 *                                                        ﹈ ﹈   
 * D.pop()            // Returns 3.  The stacks are now:   1 
 *                                                        ﹈   
 * Example 2:
 * Input: 
 * ["DinnerPlates","push","push","push","push","push","popAtStack","push","push","popAtStack","popAtStack","pop","pop","pop","pop","pop"]
 * Output: 
 * [null,null,null,null,null,null,2,null,null,2,3,1,4,-1,-1,-1]
 * 
 * Note:
 * 1 <= capacity <= 20000
 * 1 <= val <= 20000
 * 0 <= index <= 100000
 * At most 200000 calls will be made to push, pop, and popAtStack.
 */
#include <vector>
#include <stack>
#include <set>

class DinnerPlates {
private:
    int cap;
    std::vector<std::stack<int>> stacks;   // all stacks
    std::set<int> avail;                    // indices where size < cap
    std::set<int> nonEmpty;                  // indices where size > 0

public:
    DinnerPlates(int capacity) : cap(capacity) {}

    void push(int val) {
        if (avail.empty()) {
            // create a new stack at the end
            stacks.emplace_back();
            int idx = stacks.size() - 1;
            stacks[idx].push(val);
            nonEmpty.insert(idx);
            if (cap > 1) avail.insert(idx);   // not full yet
        } else {
            // use the leftmost available stack
            int idx = *avail.begin();
            stacks[idx].push(val);
            nonEmpty.insert(idx);              // in case it was empty
            if (stacks[idx].size() == cap) {
                avail.erase(idx);               // now full
            }
        }
    }

    int pop() {
        if (nonEmpty.empty()) return -1;
        int idx = *nonEmpty.rbegin();           // rightmost non‑empty
        int val = stacks[idx].top();
        stacks[idx].pop();

        if (stacks[idx].empty()) {
            nonEmpty.erase(idx);
        }
        // after popping, it definitely has room (size < cap)
        avail.insert(idx);
        return val;
    }

    int popAtStack(int index) {
        if (index < 0 || index >= stacks.size()) return -1;
        if (stacks[index].empty()) return -1;

        int val = stacks[index].top();
        stacks[index].pop();

        if (stacks[index].empty()) {
            nonEmpty.erase(index);
        }
        // after popping, it has room
        avail.insert(index);
        return val;
    }
};