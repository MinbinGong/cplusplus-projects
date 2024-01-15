// ReverseNodesInKGroup.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct ListNode {
  int val = 0;
  ListNode* next = nullptr;
  ListNode(int x = 0, ListNode* n = nullptr) : val(x), next(n) {}
};

ListNode* reverseKGroupRecursive(ListNode* head, int k) {
  if (head == nullptr || head->next == nullptr || k < 2) {
    return head;
  }

  ListNode* nextGroup = head;
  for (size_t i = 0; i < k; i++) {
    if (nextGroup) {
      nextGroup = nextGroup->next;
    } else {
      return head;
    }
  }

  ListNode* newNextGroup = reverseKGroupRecursive(nextGroup, k);
  ListNode *prev = nullptr, *cur = head;
  while (cur != nextGroup) {
    ListNode* next = cur->next;
    cur->next = prev != nullptr ? prev : newNextGroup;
    prev = cur;
    cur = next;
  }
  return prev;
}

ListNode* reverse(ListNode* prev, ListNode* begin, ListNode* end) {
  ListNode* endNext = end->next;
  for (ListNode *p = begin, *cur = p->next, *next = cur->next; cur != endNext;
       p = cur, cur = next, next = next != nullptr ? next->next : nullptr) {
    cur->next = p;
  }

  begin->next = endNext;
  prev->next = end;

  return begin;
}

ListNode* reverseKGroupIterative(ListNode* head, int k) {
  if (head == nullptr || head->next == nullptr || k < 2) {
    return head;
  }

  ListNode dummy{-1};
  dummy.next = head;

  for (ListNode *prev = &dummy, *end = head; end != nullptr; end = prev->next) {
    for (size_t i = 1; i < k && end != nullptr; i++) {
      end = end->next;
    }

    if (end == nullptr) {
      break;
    }

    prev = reverse(prev, prev->next, end);
  }

  return dummy.next;
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
