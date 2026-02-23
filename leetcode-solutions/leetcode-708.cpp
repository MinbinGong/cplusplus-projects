/*
 * Insert into a Cyclic Sorted List
 *
 * Given a node from a cyclic linked list which is sorted in ascending order, write a function to insert a value into the list such that it remains a cyclic sorted list. The given node can be a reference to any single node in the list, and may not be necessarily the smallest value in the cyclic list.
 *
 * If there are multiple suitable places for insertion, you may choose any place to insert the new value. After the insertion, the cyclic list should remain sorted.
 *
 * If the list is empty (i.e., given node is null), you should create a new single cyclic list and return the reference to that single node. Otherwise, you should return the original given node.
 * 
 * Example 1:
 *
 * Input: head = [3,4,1], insertVal = 2
 * Output: [3,4,1,2]
 * 
 * Explanation:
 * There are three nodes in the cyclic list, which are sorted in ascending order: 1, 3, 4.
 * 
 * Example 2:
 *
 * Input: head = [], insertVal = 1
 * Output: [1]
 * 
 * Explanation:
 * The list is empty (given head is null). We create a new single cyclic list and return the reference to that single node.
 * 
 * Example 3:
 *
 * Input: head = [1], insertVal = 0
 * Output: [1,0]
 * 
 * Explanation:
 * The list has only one node. insertVal is 0.
 * 
 * Note:
 * 1. All values of the nodes in the list are unique.
 * 2. The given node can be a reference to any single node in the list, and may not be necessarily the smallest value in the cyclic list.
 * 3. The inserted value insertVal is not in the list.
 * 4. The number of nodes in the given list is between [1, 10^4].
 * 5. The inserted value insertVal is not in the list.
 * 
 */
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        // 情况1：链表为空
        if (!head) {
            Node* newNode = new Node(insertVal);
            newNode->next = newNode; // 自循环
            return newNode;
        }

        Node* cur = head;
        Node* maxNode = head; // 记录最大值节点（用于处理边界情况）
        
        do {
            // 情况2：找到正常插入位置（cur->val <= insertVal <= cur->next->val）
            if (cur->val <= insertVal && insertVal <= cur->next->val) {
                insertAfter(cur, insertVal);
                return head;
            }
            // 更新最大值节点（用于处理所有数相等或插入值最大/最小的情况）
            if (cur->val >= maxNode->val) {
                maxNode = cur;
            }
            cur = cur->next;
        } while (cur != head);

        // 情况3：执行到这里说明没有找到合适的插入位置
        // 说明 insertVal 要么比所有数都大，要么比所有数都小，或者所有节点值相等
        // 统一插入到最大值节点之后
        insertAfter(maxNode, insertVal);
        return head;
    }

private:
    void insertAfter(Node* node, int val) {
        Node* newNode = new Node(val);
        newNode->next = node->next;
        node->next = newNode;
    }
};