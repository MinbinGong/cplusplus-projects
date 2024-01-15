#include <climits>
#include <queue>
#include <vector>

struct ListNode {
  int val = 0;
  ListNode* next = nullptr;
  ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
  ListNode head(-1);
  for (ListNode* p = &head; l1 != nullptr || l2 != nullptr; p = p->next) {
    int val1 = l1 == nullptr ? INT_MAX : l1->val;
    int val2 = l2 == nullptr ? INT_MAX : l2->val;

    if (val1 < val2) {
      p->next = l1;
      l1 = l1->next;
    } else {
      p->next = l2;
      l2 = l2->next;
    }
  }

  return head.next;
}

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
  if (lists.empty()) {
    return nullptr;
  }

  while (lists.size() > 1) {
    lists.push_back(mergeTwoLists(lists[0], lists[1]));
    lists.erase(lists.begin());
    lists.erase(lists.begin());
  }

  return lists.front();
}

ListNode* mergeKListsHeap(std::vector<ListNode*>& lists) {
  if (lists.empty()) {
    return nullptr;
  }

  std::priority_queue<ListNode*, std::vector<ListNode*>,
                      [](const ListNode* l, const ListNode* r) { return l->val > r->val; }>
    pq;

  for (auto i : lists) {
    if (i != nullptr) {
      pq.push(i);
    }
  }

  ListNode* dummy = new ListNode(-1);
  ListNode* tail = dummy;
  while (!pq.empty()) {
    tail->next = pq.top();
    tail = tail->next;
    pq.pop();
    if (tail->next != nullptr) {
      pq.push(tail->next);
    }
  }

  return dummy->next;
}