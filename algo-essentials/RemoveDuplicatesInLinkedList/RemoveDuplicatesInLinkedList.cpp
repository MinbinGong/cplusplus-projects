// RemoveDuplicatesInLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct ListNode {
  int val = 0;
  ListNode* next = nullptr;
  ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* deleteDuplicates(ListNode* head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }

  ListNode* newHead = deleteDuplicates(head->next);
  if (head->val = newHead->val) {
    delete head;
    head = newHead;
  } else {
    head->next = newHead;
  }
  return head;
}

ListNode* deleteDuplicates2(ListNode* head) {
  if (head == nullptr) {
    return nullptr;
  }

  for (auto slow = head, fast = head->next; fast != nullptr; fast = slow->next) {
    if (slow->val == fast->val) {
      slow->next = fast->next;
      delete fast;
    } else {
      slow = fast;
    }
  }

  return head;
}

int main() { std::cout << "Hello World!\n"; }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files
//   to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
