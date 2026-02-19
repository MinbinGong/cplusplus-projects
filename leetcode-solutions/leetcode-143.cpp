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

void reorderList1(ListNode *head) {
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

void reorderList1(ListNode* head) {
    if(!head || !head->next) return;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // After this, slow will be at the middle of the linked list
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // In case of odd length, the second half starts at slow->next
    ListNode* second = slow->next;
    slow->next = nullptr;
    
    // Reverse the second half (mid+1 onwards)
    ListNode* curr = second;
    ListNode* prev = nullptr;
    while(curr != nullptr){
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    // Reorder logic
    // Since we have reversed the second half, 
    // the first->next gets connected to second (which is now at prev)
    ListNode* first = head;
    second = prev;
    
    while(second){
        ListNode* temp1 = first->next;
        ListNode* temp2 = second->next;
        
        first->next = second;
        second->next = temp1;
        
        first = temp1;
        second = temp2;
    }
}
