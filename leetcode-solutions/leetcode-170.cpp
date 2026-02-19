/*
 * Two Sum III - Data structure design
 * 
 * Design a data structure that accepts a stream of integers and checks if it has a pair of integers that sum up to a particular value.
 * 
 * Implement the TwoSum class:
 * 1. TwoSum() Initializes the TwoSum object, with an empty array initially.
 * 2. void add(int number) Adds number to the data structure.
 * 3. boolean find(int value) Returns true if there exists any pair of numbers whose sum is equal to value, otherwise, it returns false.
 * 
 * Constraints:
 * 1. -105 <= number <= 105
 * 2. -231 <= value <= 231 - 1
 * 3. At most 104 calls will be made to add and find.
 * 4. You may assume that all the calls to add and find are valid.
 */
#include <unordered_map>
using namespace std;

class TwoSum {
public:
    /** Initialize your data structure here. */
    TwoSum() {
    }
    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        // 增加数字的计数
        counts[number]++;
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        for (const auto& [num, count] : counts) {
            int complement = value - num;
            // 在哈希表中查找补数
            if (counts.find(complement) != counts.end()) {
                // 如果补数和当前数字相同，需要确保该数字至少有2个
                if (complement != num || count > 1) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    // 哈希表存储数字及其出现次数
    unordered_map<int, int> counts; 
};