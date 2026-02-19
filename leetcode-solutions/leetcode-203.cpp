/*
 * Remove Linked List Elements
 *
 * Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val,
 * and return the new head.
 *
 * Constraints:
 * 1. The number of nodes in the list is in the range [0, 104].
 * 2. 1 <= Node.val <= 50
 * 3. 0 <= val <= 50
 * 4. The list is guaranteed to be non-empty.
 * 5. The list is guaranteed to have at least one node.
 * 6. The list is guaranteed to have at most 104 nodes.
 */
// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* removeElements(ListNode* head, int val) {
  // Dummy node that points to the head
  ListNode dummy(0);
  dummy.next = head;

  ListNode* prev = &dummy;
  ListNode* curr = head;

  while (curr != nullptr) {
    if (curr->val == val) {
      // Skip the current node
      prev->next = curr->next;
      // Free the node (optional in competitive programming)
      // delete curr;
      curr = prev->next;
    } else {
      // Move both pointers forward
      prev = curr;
      curr = curr->next;
    }
  }

  return dummy.next;
}
