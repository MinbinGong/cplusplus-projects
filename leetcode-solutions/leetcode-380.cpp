/*
 * Insert Delete GetRandom O(1)
 * 
 * Implement the RandomizedSet class:
 * 
 * RandomizedSet() Initializes the RandomizedSet object.
 * bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
 * bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.
 * int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.
 * You must implement the functions of the class such that each function works in average O(1) time complexity.
 * 
 */
#include <vector>
#include <unordered_map>
#include <cstdlib> // for rand()

class RandomizedSet {
private:
    std::vector<int> nums;
    std::unordered_map<int, int> valToIdx; // value -> index in nums

public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        // seed random number generator (optional)
        // srand(time(nullptr));
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (valToIdx.find(val) != valToIdx.end()) {
            return false; // already present
        }
        nums.push_back(val);
        valToIdx[val] = nums.size() - 1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto it = valToIdx.find(val);
        if (it == valToIdx.end()) {
            return false; // not present
        }
        int idx = it->second;
        int lastVal = nums.back();
        // swap with last element
        nums[idx] = lastVal;
        valToIdx[lastVal] = idx;
        // remove last
        nums.pop_back();
        valToIdx.erase(it);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        // assume set is non-empty
        int randomIndex = rand() % nums.size();
        return nums[randomIndex];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */