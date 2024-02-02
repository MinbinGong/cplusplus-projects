/*
Partition List

Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.
 */
struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* partition (ListNode* head, int x) {
  ListNode *lesser = nullptr;
  ListNode *greater = nullptr;
  ListNode *startLesser = nullptr;
  ListNode *startGreater = nullptr;

  ListNode *prev;
  while (head != nullptr)
  {
    prev = head;
    head = head->next;
    pre->next = nullptr;

    if (prev->val < x)
    {
      if (lesser == nullptr)
      {
        lesser = prev;
        startLesser = lesser;
      }else{
        lesser->next = prev;
        lesser = lesser->next;
      }
      
    } else {
      if (greater == nullptr)
      {
        greater = prev;
        startGreater = greater;
      }
      else {
        greater->next = prev;
        greater = greater->next;
      }
    }
    
  }
  if (startLesser == nullptr)
  {
    return startGreater;
  }
  
  if (startGreater == nullptr)
  {
    return startLesser;
  }
  lesser->next = startGreater;

  return startLesser;
}
