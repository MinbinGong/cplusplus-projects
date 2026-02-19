/*
  Remove Duplicates from Sorted List II

  Given the head of a sorted linked list, delete all nodes that have duplicate numbers,
  leaving only distinct numbers from the original list. Return the linked list sorted as well.
 */

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *n) : val(x), next(n) {}
};

ListNode *deleteDuplicates(ListNode *head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }

  ListNode *dummy = new ListNode(0, head);
  ListNode *curr = head;
  ListNode *prev = dummy;

  while (curr != nullptr) {
    if (curr->next != nullptr && curr->val == curr->next->val) {
      while (curr->next != nullptr && curr->val == curr->next->val) {
        curr = curr->next;
      }
      prev->next = curr->next;
    } else {
      prev = curr;
    }
    curr = curr->next;
  }
  return dummy->next;
}