#include <climits>

struct ListNode {
  int val = 0;
  ListNode* next = nullptr;
  ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* findInsertPos(ListNode* head, int x) {
  ListNode* pre = nullptr;
  for (ListNode* cur = head; cur != nullptr && cur->val <= x; pre = cur, cur = cur->next)
    ;

  return pre;
}

ListNode* insertionSortList(ListNode* head) {
  ListNode dummy{INT_MIN};

  for (ListNode* cur = head; cur != nullptr;) {
    auto pos = findInsertPos(&dummy, cur->val);
    ListNode* tmp = cur->next;
    cur->next = pos->next;
    pos->next = cur;
    cur = tmp;
  }

  return dummy.next;
}