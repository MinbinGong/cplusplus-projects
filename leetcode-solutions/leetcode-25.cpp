/*
 * k is a positive integer and is less than or equal to the length of the
 * linked list. If the number of nodes is not a multiple of k then left-out
 * nodes, in the end, should remain as it is.
 *
 * You may not alter the values in the list's nodes, only nodes themselves
 * may be changed.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* n) : val(x), next(n) {}
};

ListNode* reverseKGroupRecursive(ListNode* head, int k) {
    if (nullptr == head) {
        return nullptr;
    }

    int size = 0;
    ListNode* temp = head;
    while (nullptr != temp) {
        temp = temp->next;
        size++;
    }

    if (size < k) {
        return head;
    }

    ListNode *curr = head, *prev = nullptr, *next = nullptr;
    int count = 0;
    while (nullptr != curr && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    if (nullptr != next) {
        head->next = reverseKGroup(next, k);
    }

    return prev;
}

ListNode* reverseKGroupIterative(ListNode* head, int k) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode *before = dummy, *after = head;
    ListNode *curr = nullptr, *prev = nullptr, *next = nullptr;

    while (true) {
        ListNode* cursor = after;
        for (int i = 0; i < k; i++) {
            if (cursor == nullptr) {
                return dummy->next;
            }

            cursor = cursor->next;
        }

        curr = after;
        prev = before;

        for (int i = 0; i < k; i++) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        after->next = curr;
        before->next = prev;
        before = after;
        after = curr;
    }
}