/*
Merge two sorted lists
 */

struct ListNode {
    int val = 0;
    ListNode* next = nullptr;
    explicit ListNode(int x, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* mergeTwoListsRecursive(ListNode* l1, ListNode* l2) {
    if (l2 == nullptr) {
        return l1;
    }
    if (l1 == nullptr) {
        return l2;
    }

    if (l1->val > l2->val) {
        l2->next = mergeTwoListsRecursive(l1, l2->next);
        return l2;
    }
    l1->next = mergeTwoListsRecursive(l1->next, l2);
    return l1;
}

ListNode* mergeTwoListsIterative(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0), *node = dummy;
    while (l1 && l2)
    {
        if (l1->val <= l2->val)
        {
            node->next = l1;
            l1=l1->next;
        } else {
            node->next = l2;
            l2=l2->next;
        }
        node = node->next;
    }
    node->next = l1 ? l1 : l2;
    return dummy->next;
}