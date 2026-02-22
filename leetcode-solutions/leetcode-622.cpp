/*
 * Design Circular Queue
 * 
 * Design your implementation of the circular queue. The circular queue is a linear data structure in which the
 * operations are performed based on FIFO (First In First Out) principle and the last position is connected back to
 * the first position to make a circle. It is also called "Ring Buffer".
 * 
 * One of the benefits of the circular queue is that we can make use of the spaces in front of the queue. In a
 * normal queue, once the queue becomes full, we cannot insert the next element even if there is a space in front of
 * the queue. But using the circular queue, we can use the space to store new values.
 * 
 * Implementation the MyCircularQueue class:
 * 
 * MyCircularQueue(k) Initializes the object with the size of the queue to be k.
 * int Front() Gets the front item from the queue. If the queue is empty, return -1.
 * int Rear() Gets the last item from the queue. If the queue is empty, return -1.
 * boolean enQueue(int value) Inserts an element into the circular queue. Return true if the operation is successful.
 * 
 * boolean deQueue() Deletes an element from the circular queue. Return true if the operation is successful.
 * int Rear() Gets the last item from the queue. If the queue is empty, return -1.
 * boolean isEmpty() Checks whether the circular queue is empty or not.
 * boolean isFull() Checks whether the circular queue is full or not.
 * 
 * Note:
 * All the values will be in the range of [0, 1000].
 * The number of operations will be in the range of [1, 1000].
 * Please do not use the built-in Queue library.
 * 
 */
#include <vector>
using namespace std;

class MyCircularQueue {
private:
    vector<int> data;   // fixed-size array
    int front;          // index of the front element
    int rear;           // index of the rear element
    int count;          // current number of elements
    int capacity;       // maximum capacity

public:
    MyCircularQueue(int k) {
        data.resize(k);
        capacity = k;
        front = 0;
        rear = -1;
        count = 0;
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;
        rear = (rear + 1) % capacity;
        data[rear] = value;
        count++;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        front = (front + 1) % capacity;
        count--;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return data[front];
    }
    
    int Rear() {
        if (isEmpty()) return -1;
        return data[rear];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == capacity;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */