/*
 * Design Circular Deque
 *
 * Design your implementation of the circular double-ended queue (deque).
 *
 * Your implementation should support following operations:
 *
 * MyCircularDeque(k): Constructor, set the size of the deque to be k.
 * insertFront(): Adds an item at the front of Deque. Return true if the operation is successful.
 * insertLast(): Adds an item at the rear of Deque. Return true if the operation is successful.
 * deleteFront(): Deletes an item from the front of Deque. Return true if the operation is successful.
 * deleteLast(): Deletes an item from the rear of Deque. Return true if the operation is successful.
 * getFront(): Gets the front item from the Deque. If the deque is empty, return -1.
 * getRear(): Gets the last item from Deque. If the deque is empty, return -1.
 * isEmpty(): Checks whether Deque is empty or not. 
 * isFull(): Checks whether Deque is full or not.
 *
 * Note:
 *
 * All values will be in the range of [0, 1000].
 * The number of operations will be in the range of [1, 1000].
 * Please do not use the built-in Deque library.
 *
 */
#include <vector>
#include <list>

using namespace std;

class MyCircularDeque1 {
private:
    vector<int> buffer;
    int front;
    int rear;
    int capacity;
    int count;

public:
    /** Initialize with size k */
    MyCircularDeque1(int k) {
        capacity = k;
        buffer.resize(k);
        front = 0;
        rear = 0;
        count = 0;
    }
    
    /** Adds an item at the front */
    bool insertFront(int value) {
        if (isFull()) return false;
        front = (front - 1 + capacity) % capacity;
        buffer[front] = value;
        count++;
        return true;
    }
    
    /** Adds an item at the rear */
    bool insertLast(int value) {
        if (isFull()) return false;
        buffer[rear] = value;
        rear = (rear + 1) % capacity;
        count++;
        return true;
    }
    
    /** Deletes an item from the front */
    bool deleteFront() {
        if (isEmpty()) return false;
        front = (front + 1) % capacity;
        count--;
        return true;
    }
    
    /** Deletes an item from the rear */
    bool deleteLast() {
        if (isEmpty()) return false;
        rear = (rear - 1 + capacity) % capacity;
        count--;
        return true;
    }
    
    /** Get the front item */
    int getFront() {
        if (isEmpty()) return -1;
        return buffer[front];
    }
    
    /** Get the last item */
    int getRear() {
        if (isEmpty()) return -1;
        return buffer[(rear - 1 + capacity) % capacity];
    }
    
    /** Checks whether the deque is empty */
    bool isEmpty() {
        return count == 0;
    }
    
    /** Checks whether the deque is full */
    bool isFull() {
        return count == capacity;
    }
};

class MyCircularDeque2 {
private:
    list<int> data;
    int capacity;
    
public:
    MyCircularDeque2(int k) {
        capacity = k;
    }
    
    bool insertFront(int value) {
        if (data.size() == capacity) return false;
        data.push_front(value);
        return true;
    }
    
    bool insertLast(int value) {
        if (data.size() == capacity) return false;
        data.push_back(value);
        return true;
    }
    
    bool deleteFront() {
        if (data.empty()) return false;
        data.pop_front();
        return true;
    }
    
    bool deleteLast() {
        if (data.empty()) return false;
        data.pop_back();
        return true;
    }
    
    int getFront() {
        return data.empty() ? -1 : data.front();
    }
    
    int getRear() {
        return data.empty() ? -1 : data.back();
    }
    
    bool isEmpty() {
        return data.empty();
    }
    
    bool isFull() {
        return data.size() == capacity;
    }
};