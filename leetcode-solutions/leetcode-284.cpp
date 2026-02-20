/*
 * Peeking Iterator
 * 
 * Design an iterator that supports the peek operation on an existing iterator in addition to the hasNext and the next operations.
 * 
 * Implement the PeekingIterator class:
 * 1. PeekingIterator(Iterator<int> nums) Initializes the object with the given integer iterator iterator.
 * 2. int next() Returns the next element in the array and moves the pointer to the next element.
 * 3. boolean hasNext() Returns true if there are still elements in the array.
 * 4. int peek() Returns the next element in the array without moving the pointer.
 * 
 * Constraints:
 * 1. 1 <= nums.length <= 1000
 * 2. 1 <= nums[i] <= 1000
 * 3. All the calls to next and peek are valid.
 * 
 */
#include <vector>
using namespace std;

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
    Data* data;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};

class PeekingIterator : public Iterator {
private:
    int _next;          // 缓存的下一个元素值
    bool _has_next;     // 是否还有下一个元素

public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        // 初始化时，先获取第一个元素
        _has_next = Iterator::hasNext();
        if (_has_next) {
            _next = Iterator::next();
        }
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        return _next;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        int res = _next;                    // 返回当前缓存的值
        _has_next = Iterator::hasNext();     // 更新是否有下一个元素
        if (_has_next) {
            _next = Iterator::next();        // 预取下一个元素
        }
        return res;
    }

    bool hasNext() const {
        return _has_next;
    }
};