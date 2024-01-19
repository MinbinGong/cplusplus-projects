/*
 * Rotate List
 *
 * Given the head of a linked list, rotate the list to the right by k places
 *
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 *
 * Approach
 * 1. Implement a function length_LL to calculate the length of the linked list.
 * 2. Implement a function reverse to reverse the first k nodes of the linked list.
 * 3. Calculate the effective rotation value by taking the modulo of k with the length of the linked list (k = k % len).
 * 4. If k is zero, return the original head as no rotation is needed
 * 5. Reverse the entire linked list using the reverse function with the length of the linked list as the parameter
 * 6. Traverse the linked list using a pointer (ptr1) until the (k+1)th node and store its address.
 * 7. Reverse the first k nodes using the reverse function with the original head and k as parameters. Now, the head is pointing to the kth node.
 * 8. Swap the addresses of the original head and the temporary head obtained after reversing the first k nodes.
 * 9. Connect the kth node to the remaining (length-k) nodes by reversing them using the reverse function with the (k+1)th node and the length of the linked list as parameters.
 * 10. Return the modified head.
 */

 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

int ll_length(ListNode *head) {
    if (head == nullptr) {
        return 0;
    }

    int count = 0;
    ListNode *temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    return count;
}

ListNode* ll_reverse(ListNode* head, int k) {
    if (head == nullptr) {
        return head;
    }

    int count = 0;
    ListNode *curr = head, *prev = nullptr, *next = nullptr;
    while (curr != nullptr && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    return prev;
}

ListNode* rotate_right(ListNode* head, int k) {
    if (head == nullptr) {
        return head;
    }

    int len = ll_length(head);
    k = k % len;
    if (k == 0) {
        return head;
    }

    head = ll_reverse(head, len);
    ListNode *ptr1 = head;
    ListNode *temp_head = nullptr;
    int count = 0;
    while (count < k) {
        ptr1 = ptr1->next;
        count++;
    }

    temp_head = ll_reverse(head, k);

    swap(temp_head, head);
    temp_head->next = ll_reverse(ptr1, len);
    return head;
}
