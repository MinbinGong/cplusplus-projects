/**
 * 1474. Delete N Nodes After M Nodes of a Linked List
 * 
 * Given the head of a linked list and two integers m and n. Traverse the linked list and remove some nodes in the following way:
 * 
 * Start with the head as the current node.
 * Keep the first m nodes starting with the current node.
 * Remove the next n nodes
 * Keep repeating steps 2 and 3 until you reach the end of the list.
 * Return the head of the modified list after removing the mentioned nodes.
 * 
 * Follow up question: How can you solve this problem by modifying the list in-place?
 * 
 * Example 1:
 * 
 * Input: head = [1,2,3,4,5,6,7,8,9,10,11,12,13], m = 2, n = 3
 * Output: [1,2,6,7,11,12]
 * Explanation: Keep the first (m = 2) nodes starting from the head of the linked List  (1 ->2) show in black nodes.
 * 
 * Example 2:
 * 
 * Input: head = [1,2,3,4,5,6,7,8,9,10,11], m = 1, n = 3
 * Output: [1,5,9]
 * Explanation: Keep the first (m = 1) node starting from the head of the linked List (1 ->2) show in black nodes.
 * Remove the next (n = 3) nodes.
 * Keep repeating steps 2 and 3 until you reach the end of the list.
 * 
 * Example 3:
 * 
 * Input: head = [1,2,3,4,5,6,7,8,9,10,11], m = 3, n = 1
 * Output: [1,2,3,5,6,7,9,10,11]
 * Explanation: Keep the first (m = 3) nodes starting from the head of the linked List (1 ->2 ->3) show in black nodes.
 * Remove the next (n = 1) node.
 * 
 * Note:
 * 1 <= n <= 500
 * arr.length == 2n
 * 1 <= arr[i] <= 10^3
 * 1 <= k <= n
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
    ListNode* deleteNodes(ListNode* head, int m, int n) {
        ListNode* current = head;
        ListNode* lastM = head;
        
        while (current != nullptr) {
            // keep m nodes
            int mCount = m, nCount = n;
            while (current != nullptr && mCount > 0) {
                lastM = current;
                current = current->next;
                mCount--;
            }
            
            // delete n nodes
            while (current != nullptr && nCount > 0) {
                current = current->next;
                nCount--;
            }
            
            // connect the m-th node to the node after the n deleted nodes
            lastM->next = current;
        }
        
        return head;
    }
};