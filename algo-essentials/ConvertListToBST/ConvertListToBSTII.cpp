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

TreeNode *sortedListToBST(ListNode *&list, int start, int end)
{
    if (start > end)
    {
        return nullptr;
    }

    int mid = start + (end - start) >> 1;
    TreeNode *leftChild = sortedListToBST(list, start, mid - 1);
    TreeNode *parent = new TreeNode(list->val);
    parent->left = leftChild;
    list = list->next;
    parent->right = sortedListToBST(list, mid + 1, end);
    return parent;
}

TreeNode *sortedListToBST(ListNode *head)
{
    int len = 0;
    ListNode *p = head;
    while (p)
    {
        len++;
        p = p->next;
    }

    return sortedListToBST(head, 0, len - 1);
}
