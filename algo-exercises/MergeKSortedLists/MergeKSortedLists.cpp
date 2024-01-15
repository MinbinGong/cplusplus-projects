// MergeKSortedLists.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <vector>

#include "pch.h"

typedef struct NodeTag {
  int data;
  struct NodeTag *next;
} Node;

struct Comparator {
  bool operator()(Node *a, Node *b) { return a->data > b->data; }
};

Node *mergeKLists(std::vector<Node *> &arr) {
  Node *head = NULL, *last = NULL;
  size_t k = arr.size();

  std::priority_queue<Node *, std::vector<Node *>, Comparator> pq;

  for (size_t i = 0; i < k; i++) {
    pq.push(arr[i]);
  }

  while (!pq.empty()) {
    Node *top = pq.top();
    pq.pop();

    if (top->next != NULL) {
      pq.push(top->next);
    }

    if (head == NULL) {
      head = top;
      last = top;
    } else {
      last->next = top;
      last = top;
    }
  }

  return head;
}

void printList(Node *head) {
  while (head != NULL) {
    std::cout << head->data << " ";
    head = head->next;
  }
}

Node *newNode(int d) {
  Node *newNode = new Node();

  newNode->data = d;
  newNode->next = NULL;

  return newNode;
}
int main() {
  std::vector<Node *> arr(3);

  arr[0] = newNode(1);
  arr[0]->next = newNode(3);
  arr[0]->next->next = newNode(5);
  arr[0]->next->next->next = newNode(7);

  arr[1] = newNode(2);
  arr[1]->next = newNode(4);
  arr[1]->next->next = newNode(6);
  arr[1]->next->next->next = newNode(8);

  arr[2] = newNode(0);
  arr[2]->next = newNode(9);
  arr[2]->next->next = newNode(10);
  arr[2]->next->next->next = newNode(11);

  Node *head = mergeKLists(arr);

  printList(head);

  return 0;
}