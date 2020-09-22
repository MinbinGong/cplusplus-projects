#include <vector>
using namespace std;

struct TrieNode
{
    vector<TrieNode *> child;
    bool last;
    TrieNode() : child(2, NULL), last(false){};
};

void insert(int val)
{
    TrieNode *cur = root;
    for (int i = 31; i >= 0; i--)
    {
        int v = (val >> i) & 1;
        if (!cur->child[v])
            cur->child[v] = new TrieNode();
        cur = cur->child[v];
    }
    cur->last = true;
}

int search(int val)
{
    cout << val << endl;
    TrieNode *cur = root;
    int res = 0;
    for (int i = 31; i >= 0; i--)
    {
        int v = (val >> i) & 1;
        if (cur->child[1 - v])
        {
            res |= ((1 - v) << i);
            cur = cur->child[1 - v];
        }
        else
        {
            res |= (v << i);
            cur = cur->child[v];
        }
    }
    return res;
}

TrieNode *root;

int findMaximumXOR(vector<int> &nums)
{
    root = new TrieNode();
    int mx = 0;
    for (auto num : nums)
        insert(num);
    for (auto num : nums)
    {
        mx = max(num ^ search(num), mx);
    }
    return mx;
}