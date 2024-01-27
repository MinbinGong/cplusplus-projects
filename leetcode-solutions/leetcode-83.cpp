/*
Remove Duplicates from Sorted List

Given the head of a sorted linked list, delete all duplicates such that each element appears only once.
Return the linked list sorted as well.
 */
struct ListNode {
  int val = 0;
  ListNode* next = nullptr;
  explicit ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* deleteDuplicates(ListNode* head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }
  ListNode* temp = head;

  while (temp->next != nullptr) {
    if (temp->val == temp->next->val) {
      temp->next = temp->next->next;
    } else {
      temp = temp->next;
    }
  }
  return head;
}