/**
 * 1721. Swapping Nodes in a Linked List
 * 
 * You are given the head of a linked list, and an integer k.
 * 
 * Return the head of the linked list after swapping the values of the kth node from the beginning and the kth node from the end (the list is 1-indexed).
 * 
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [1,4,3,2,5]
 * 
 * Example 2:
 * Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
 * Output: [7,9,6,6,8,7,3,0,9,5]
 * 
 * Constraints:
 * The number of nodes in the list is n.
 * 1 <= k <= n <= 105
 * 0 <= Node.val <= 100
 * 
 */
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode *first = head, *second = head;
        
        // Move first to the k-th node from the beginning
        for (int i = 1; i < k; ++i) {
            first = first->next;
        }
        
        // Remember the k-th node from start
        ListNode *kthFromStart = first;
        
        // Move first to the end; second will then be at the k-th node from the end
        while (first->next) {
            first = first->next;
            second = second->next;
        }
        
        // Swap values of the two nodes
        swap(kthFromStart->val, second->val);
        
        return head;
    }
};