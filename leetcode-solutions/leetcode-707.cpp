/*
 * Design Linked List
 *
 * Design your implementation of the linked list. You can choose to use a singly or doubly linked list.
 * A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node.
 * If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.
 *
 * Implement the MyLinkedList class:
 *
 * MyLinkedList() Initializes the MyLinkedList object.
 * int get(int index) Get the value of the indexth node in the linked list. If the index is invalid, return -1.
 * void addAtHead(int val) Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
 * void addAtTail(int val) Append a node of value val as the last element of the linked list.
 * void addAtIndex(int index, int val) Add a node of value val before the indexth node in the linked list. If index equals the length of the linked list, the node will be appended to the end of the linked list. If index is greater than the length, the node will not be inserted.
 * void deleteAtIndex(int index) Delete the indexth node in the linked list, if the index is valid.
 * 
 * Note:
 * 1. All values will be in the range of [0, 1000].
 * 2. The number of operations will be in the range of [1, 1000].
 * 3. Please do not use the built-in LinkedList library.
 * 4. The hash function is not necessary to be a hash function.
 *  
 */
class MyLinkedList {
private:
    struct Node {
        int val;
        Node* prev;
        Node* next;
        Node(int x) : val(x), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;  // 虚拟头节点
    Node* tail;  // 虚拟尾节点
    int size;    // 链表实际长度

public:
    MyLinkedList() {
        head = new Node(-1);  // 虚拟头
        tail = new Node(-1);  // 虚拟尾
        head->next = tail;
        tail->prev = head;
        size = 0;
    }
    
    int get(int index) {
        if (index < 0 || index >= size) return -1;
        Node* cur = head->next;
        while (index--) cur = cur->next;
        return cur->val;
    }
    
    void addAtHead(int val) {
        addAtIndex(0, val);
    }
    
    void addAtTail(int val) {
        addAtIndex(size, val);
    }
    
    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) return;
        Node* prev = head;
        for (int i = 0; i < index; ++i) prev = prev->next;
        Node* next = prev->next;
        Node* newNode = new Node(val);
        prev->next = newNode;
        newNode->prev = prev;
        newNode->next = next;
        next->prev = newNode;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        Node* cur = head->next;
        while (index--) cur = cur->next;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
        size--;
    }
    
    // 析构函数（可选，用于清理内存）
    ~MyLinkedList() {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }
};