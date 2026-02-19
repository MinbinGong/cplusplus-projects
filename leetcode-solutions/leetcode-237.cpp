/*
 * Delete Node in a Linked List
 *
 * Write a function to delete a node in a singly-linked list. You will not be given access to the head of the list,
 * instead you will be given access to the node to be deleted directly.
 *
 * It is guaranteed that the node to be deleted is not a tail node in the list.
 *
 * Constraints:
 * 1. The number of the nodes in the given list is in the range [2, 1000].
 * 2. -1000 <= Node.val <= 1000
 * 3. The value of each node in the list is unique.
 * 4. The node to be deleted is in the list and is not a tail node
 */
// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  void deleteNode(ListNode* node) {
    // node is the node to be deleted (not the tail)
    ListNode* temp = node->next;  // the node after the one to delete
    node->val = temp->val;        // copy its value
    node->next = temp->next;      // bypass temp
    delete temp;                  // free memory (optional)
  }
};