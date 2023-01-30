struct TreeNode
{
    int val = 0;
    TreeNode *left = nullptr, *right = nullptr;
    TreeNode(int x = 0, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(x), left(l), right(r) {}
};

struct ListNode
{
    int val = 0;
    ListNode *next = nullptr;
    ListNode(int x = 0, ListNode *n = nullptr) : val(x), next(n) {}
};

ListNode *cutAtMiddle(ListNode *head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    ListNode *fast = head;
    ListNode *slow = head;
    ListNode *prev_slow = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        prev_slow = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    prev_slow->next = nullptr;
    return slow;
}

TreeNode *sortedListToBST(ListNode *head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    if (head->next == nullptr)
    {
        return new TreeNode(head->val);
    }

    ListNode *mid = cutAtMiddle(head);

    TreeNode *root = new TreeNode(mid->val);
    root->left = sortedListToBST(head);
    root->right = sortedListToBST(mid->next);

    return root;
}
