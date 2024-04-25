/*
 * Reorder List
 *
 * You are given the head of a singly linked-list. The list can be represented as:

 * L0 → L1 → … → Ln - 1 → Ln
 * Reorder the list to be on the following form:
 * 
 * L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
 * You may not modify the values in the list's nodes. Only nodes themselves may be changed.
 */
struct ListNode {
    int val = 0;
    ListNode *next = nullptr;
    explicit ListNode(int x = 0, ListNode *n = nullptr) : val(x), next(n) {}
};

ListNode *reverseList(ListNode *head) {
  if (!head || !head->next) {
    return head;
  }

  ListNode *prev = nullptr;
  ListNode *next = nullptr;
  ListNode *temp = head;

  while (temp) {
    next = temp->next;
    temp->next = prev;
    prev = temp;
    temp = next;
  }

  return prev;
}

void reorderList(ListNode *head) {
  ListNode *slow = head;
  ListNode *fast = head;
  ListNode *head2 = nullptr;

  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  head2 = reverseList(slow->next);

  slow->next = nullptr;

  ListNode *a = head;
  ListNode *b = head2;

  while (a && b) {
    ListNode *a2 = a->next;
    ListNode *b2 = b->next;
    b->next = a2;
    a->next = b;
    if (a2 && !b2) {
      b->next = a2;
      return;
    }

    a = a2;
    b = b2;
  }
}
