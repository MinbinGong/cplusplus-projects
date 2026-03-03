/**
 * 1429. First Unique Number
 * 
 * You have a queue of integers, you need to retrieve the first unique integer in the queue.
 * 
 * Implement the FirstUnique class:
 * 
 * FirstUnique(int[] nums) Initializes the object with the numbers in the queue.
 * int showFirstUnique() returns the value of the first unique integer of the queue, and returns -1 if there is no such integer.
 * void add(int value) insert value to the queue.
 * 
 * Example 1:
 * 
 * Input: 
 * ["FirstUnique","showFirstUnique","add","showFirstUnique","add","showFirstUnique","add","showFirstUnique"]
 * [[[2,3,5]],[],[5],[],[2],[],[3],[]]
 * Output: 
 * [null,2,null,2,null,3,null,-1]
 * Explanation: 
 * FirstUnique firstUnique = new FirstUnique([2,3,5]);
 * firstUnique.showFirstUnique(); // return 2
 * firstUnique.add(5);            // the queue is now [2,3,5,5]
 * firstUnique.showFirstUnique(); // return 2
 * firstUnique.add(2);            // the queue is now [2,3,5,5,2]
 * firstUnique.showFirstUnique(); // return 3
 * firstUnique.add(3);            // the queue is now [2,3,5,5,2,3]
 * firstUnique.showFirstUnique(); // return -1
 * 
 * Example 2:
 * 
 * Input: 
 * ["FirstUnique","showFirstUnique","add","add","add","add","add","showFirstUnique"]
 * [[[7,7,7,7,7,7]],[],[7],[3],[3],[7],[17],[]]
 * Output: 
 * [null,-1,null,null,null,null,null,17]
 * Explanation: 
 * FirstUnique firstUnique = new FirstUnique([7,7,7,7,7,7]);
 * firstUnique.showFirstUnique(); // return -1
 * firstUnique.add(7);            // the queue is now [7,7,7,7,7,7,7]
 * firstUnique.add(3);            // the queue is now [7,7,7,7,7,7,7,3]
 * firstUnique.add(3);            // the queue is now [7,7,7,7,7,7,7,3,3]
 * firstUnique.add(7);            // the queue is now [7,7,7,7,7,7,7,3,3,7,17]
 * firstUnique.showFirstUnique(); // return 17
 * 
 * Note:
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^8
 * 1 <= value <= 10^8
 * At most 50000 calls will be made to showFirstUnique and add.
 * 
 */
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;

class FirstUnique {
private:
    // Doubly linked list to maintain order of unique numbers
    list<int> uniqueList;
    // Map from value to its iterator in the list.
    // If the value is duplicate, the iterator is set to uniqueList.end()
    unordered_map<int, list<int>::iterator> posMap;

public:
    FirstUnique(vector<int>& nums) {
        for (int num : nums) {
            add(num);
        }
    }

    int showFirstUnique() {
        if (uniqueList.empty()) return -1;
        return uniqueList.front();
    }

    void add(int value) {
        auto it = posMap.find(value);
        if (it == posMap.end()) {
            // First time seen: insert at back of list
            uniqueList.push_back(value);
            list<int>::iterator inserted = prev(uniqueList.end());
            posMap[value] = inserted;
        } else if (it->second != uniqueList.end()) {
            // Second time seen: remove from list and mark as duplicate
            uniqueList.erase(it->second);
            it->second = uniqueList.end(); // mark as duplicate
        }
        // else it's already duplicate, do nothing
    }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */