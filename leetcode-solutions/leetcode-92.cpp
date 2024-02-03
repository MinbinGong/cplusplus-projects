/*
 * Reverse Linked List
 *
 * Given the head of a singly linked list and two integers left and right where left <= right,
 * reverse the nodes of the list from position left to position right, and return the reversed list.
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *n) : val(x), next(n) {}
};

ListNode *reverseBetween(ListNode *head, int left, int right) {
    if (head == nullptr) {
        return head;
    }

    ListNode *reversedHead = nullptr;
    ListNode *reversedTail = nullptr;

    ListNode *before = nullptr;
    ListNode *temp = head;
    ListNode *after = nullptr;

    int index = 1;
    while (temp) {
        after = temp->next;

        if (index < left) {
            before = temp;
        } else if (index >= left && index <= right) {
            if (before && before->next) {
                before->next = nullptr;
            }

            temp->next = nullptr;
            
            if (reversedHead == nullptr) {
                reversedHead = temp;
                reversedTail = temp;
            } else {
                temp->next = reversedHead;
                reversedHead = temp;
            }
        }

        temp = after;

        if (index == right) {
            break;
        }

        index++;
    }

    if (before) {
        before->next = reversedHead;
    } else {
        head = reversedHead;
    }

    reversedTail->next = after;

    return head;
}
