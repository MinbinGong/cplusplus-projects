/*
 * Copy List with Random Pointer
 * 
 * A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.
 * 
 * Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.
 * 
 * For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.
 * 
 * Return the head of the copied linked list.
 * 
 * The linked list is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:
 * 
 * val: an integer representing Node.val
 * random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not point to any node.
 */

 // Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

Node* copyRandomList(Node* head) {
    if (!head) return nullptr;

    // **First Pass: Interweave original and copied nodes**
    Node* temp = head;
    while (temp) {
        Node* node = new Node(temp->val);
        node->next = temp->next;
        temp->next = node;
        temp = node->next;
    }

    // **Second Pass: Assign random pointers**
    temp = head;
    while (temp) {
        Node* node = temp->next; // The copy
        // The copy's random pointer points to the next of the original's random pointer
        if (temp->random) {
            node->random = temp->random->next;
        } else {
            node->random = nullptr;
        }
        temp = node->next; // Move to the next original node
    }

    // **Third Pass: Separate the two lists**
    Node* newHead = head->next;
    temp = head;
    while (temp) {
        Node* node = temp->next;
        // Restore original list's next pointer
        temp->next = node->next; 
        
        // Set copied list's next pointer
        if (node->next) {
            node->next = node->next->next;
        }
        
        // Move to the next original node
        temp = temp->next;
    }
    
    return newHead; 
}
