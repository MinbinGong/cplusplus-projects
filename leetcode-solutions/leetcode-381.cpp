/*
 * Insert Delete GetRandom O(1) - Duplicates allowed
 * 
 * Design a data structure that supports all following operations in average O(1) time.
 * 
 * Note: Duplicate elements are allowed.
 * 
 * insert(val): Inserts an item val to the collection.
 * remove(val): Removes an item val from the collection if present.
 * getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.
 * 
 */
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>

class RandomizedCollection {
private:
    std::vector<int> nums;
    std::unordered_map<int, std::unordered_set<int>> idxMap; // value -> set of indices

public:
    /** Initialize your data structure here. */
    RandomizedCollection() {}

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool isNew = (idxMap.find(val) == idxMap.end());
        // Add to vector
        nums.push_back(val);
        // Record index in the map set
        idxMap[val].insert(nums.size() - 1);
        return isNew;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        auto it = idxMap.find(val);
        if (it == idxMap.end()) return false; // not present

        // Get an index of val to remove (any one)
        int idxToRemove = *(it->second.begin());
        // Last element in vector
        int lastIdx = nums.size() - 1;
        int lastVal = nums[lastIdx];

        // If the element to remove is not the last one, swap with last
        if (idxToRemove != lastIdx) {
            // Swap values in vector
            nums[idxToRemove] = lastVal;
            // Update index for lastVal: remove lastIdx, add idxToRemove
            idxMap[lastVal].erase(lastIdx);
            idxMap[lastVal].insert(idxToRemove);
        }

        // Remove the element from vector and map
        nums.pop_back();
        // Erase the removed index from val's set
        it->second.erase(idxToRemove);
        if (it->second.empty()) {
            idxMap.erase(it);
        }
        return true;
    }

    /** Get a random element from the collection. */
    int getRandom() {
        // Random index in [0, nums.size()-1]
        int randomIndex = rand() % nums.size();
        return nums[randomIndex];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */