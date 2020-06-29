struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *oddEvenList(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return;
    ListNode *oddHead{nullptr}, *evenHead{nullptr}, *oddWalker{nullptr}, *evenWalker{nullptr};
    ListNode *walker{head};

    int counter{1};
    while (walker != nullptr)
    {
        if (counter % 2 == 0)
        {
            if (evenHead == nullptr)
            {
                evenHead = walker;
            }
            else
            {
                evenWalker->next = walker;
            }
            evenWalker = walker;
        }
        else
        {
            if (oddHead == nullptr)
            {
                oddHead = walker;
            }
            else
            {
                oddWalker->next = walker;
            }
            oddWalker = walker;
        }
        walker = walker->next;
        ++counter;
    }

    if (counter % 2 == 0)
    {
        evenWalker->next = nullptr;
    }
    else
    {
        oddWalker->next = nullptr;
    }
    oddWalker->next = evenHead;

    return oddHead;
}