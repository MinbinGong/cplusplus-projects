struct ListNode {
  int val = 0;
  ListNode* next = nullptr;
  ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
  if (l1 == nullptr) {
    return l2;
  }

  if (l2 == nullptr) {
    return l1;
  }

  ListNode dummy(-1);
  ListNode* p = &dummy;
  for (; l1 != nullptr && l2 != nullptr; p = p->next) {
    if (l1->val > l2->val) {
      p->next = l2;
      l2 = l2->next;
    } else {
      p->next = l1;
      l1 = l1->next;
    }
  }

  return dummy.next;
}