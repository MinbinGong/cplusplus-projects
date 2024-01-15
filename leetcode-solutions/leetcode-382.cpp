/*
Linked List Random Node

题目描述
给定一个单向链表，要求设计一个算法，可以随机取得其中的一个数字。

题解
不同于数组，在未遍历完链表前，我们无法知道链表的总长度。这里我们就可以使用水库采
样：遍历一次链表，在遍历到第 m 个节点时，有 m1 的概率选择这个节点覆盖掉之前的节点选择。
 */
#include <random>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* n) : val(x), next(n) {}
};

int getRandom(ListNode* head) {
  int ans = head->val;
  ListNode* node = head->next;
  int i = 2;
  while (node) {
    if ((rand() % i) == 0) {
      ans = node->val;
    }
    ++i;
    node = node->next;
  }
  return ans;
}