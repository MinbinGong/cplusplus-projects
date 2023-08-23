/*
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 */
#include <vector>
#include <queue>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *merge_two_list(ListNode *l1, ListNode *l2) {
    if (l1 == nullptr) {
        return l2;
    }
    if (l2 == nullptr) {
        return l1;
    }
    if (l1->val <= l2->val) {
        l1->next = merge_two_list(l1->next, l2);
        return l1;
    }
    l2->next = merge_two_list(l1, l2->next);
    return l2;
}

ListNode *break_and_join(int start, int end, std::vector<ListNode *> &lists) {
    if (start > end) {
        return nullptr;
    }
    if (start == end) {
        return lists[start];
    }
    int mid = start + (end - start) / 2;
    ListNode *list1 = break_and_join(start, mid, lists);
    ListNode *list2 = break_and_join(mid + 1, end, lists);

    return merge_two_list(list1, list2);
}

ListNode *merge_k_lists(std::vector<ListNode *> &lists) {
    int k = lists.size();

    if (k == 0) {
        return nullptr;
    }
    return break_and_join(0, k - 1, lists);
}

ListNode *mergeKLists(std::vector<ListNode *> &lists) {
    auto cmp = [](ListNode *a, ListNode *b) { return a->val > b->val; };
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> pq(cmp);

    for (auto list: lists) {
      if (list)
      {
        pq.push(list);
      }
      
    }

    ListNode dummy(0);
    ListNode *curr = &dummy;
    while (!pq.empty())
    {
      auto node = pq.top();
      pq.pop();

      curr->next = node;
      curr = curr->next;

      if (node->next)
      {
        pq.push(node->next);
      }
    }
    return dummy.next;
}