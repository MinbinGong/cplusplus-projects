struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    if (l1 == nullptr || l2 == nullptr)
        return nullptr;
    int value = l1->val + l2->val;
    int carry = 0;
    if (value >= 10)
    {
        carry = 1;
        value -= 10;
    }

    ListNode *l3 = new ListNode(value), *p = l3;
    l1 = l1->next;
    l2 = l2->next;
    while (l1 != nullptr || l2 != nullptr || carry != 0)
    {
        int tmp1 = 0, tmp2 = 0;
        if (l1)
            tmp1 = l1->val;
        if (l2)
            tmp2 = l2->val;
        value = tmp1 + tmp2 + carry;
        if (value >= 10)
        {
            carry = 1;
            value -= 10;
        }
        else
        {
            carry = 0;
        }
        ListNode *tmpNode = new ListNode(value);
        p->next = tmpNode;
        p = p->next;
        if (l1)
            l1 = l1->next;
        if (l2)
            l2 = l2->next;
    }

    return l3;
}