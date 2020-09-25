#include <vector>
#include <queue>
using namespace std;

class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

vector<vector<int>> levelOrder(Node *root)
{
    vector<vector<int>> ans;
    vector<int> v;
    if (!root)
        return ans;
    queue<Node *> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty())
    {
        Node *n = q.front();
        q.pop();
        if (n == NULL)
        {
            if (!q.empty())
                q.push(NULL);
            ans.push_back(v);
            v.clear();
        }
        else
        {
            v.push_back(n->val);
            for (int i = 0; i < n->children.size(); i++)
                q.push(n->children[i]);
        }
    }
    return ans;
}
