#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
using namespace std;

#if DEBUG
int countOfRange(vector<int> &nums, int lower, int upper)
{
    multiset<long> mySet{0};

    int res{0};
    long cumulative{0};

    for (size_t i = 0; i < nums.size(); i++)
    {
        cumulative += nums[i];
        res += distance(mySet.lower_bound(cumulative - upper), mySet.upper_bound(cumulative - lower));
        mySet.insert(cumulative);
    }

    return res;
}
#else

class SegmentTreeNode
{
public:
    long min;
    long max;
    int count; //number of values in [min, max]
    SegmentTreeNode *left;
    SegmentTreeNode *right;
    SegmentTreeNode(long min, long max, int count)
    {
        this->min = min;
        this->max = max;
        this->count = count;
        left = right = NULL;
    }
};

SegmentTreeNode *root;

SegmentTreeNode *build(vector<long> &sum, int start, int end)
{
    SegmentTreeNode *root = new SegmentTreeNode(sum[start], sum[end], 0);
    if (start == end)
    {
        return root;
    }
    else
    {
        int middle = (start + end) / 2;
        root->left = build(sum, start, middle);
        root->right = build(sum, middle + 1, end);
        return root;
    }
}

void modify(SegmentTreeNode *root, long value)
{
    if (root == NULL || value < root->min || value > root->max)
        return;
    // now value is between root->min and root->max
    root->count += 1;
    if (root->min == root->max)
    {
        return;
    }
    else
    {
        modify(root->left, value);
        modify(root->right, value);
    }
}

int query(SegmentTreeNode *root, long min, long max)
{
    if (root == NULL || max < root->min || min > root->max)
        return 0;
    if (min <= root->min && max >= root->max)
        return root->count;
    return query(root->left, min, max) + query(root->right, min, max);
}

int countRangeSum(vector<int> &nums, int lower, int upper)
{
    if (nums.size() == 0)
        return 0;
    unordered_set<long> ssum;
    long tmpSum = 0;
    for (auto n : nums)
    {
        tmpSum += n;
        ssum.insert(tmpSum);
    }
    // copy the set to a vector
    vector<long> sum;
    for (auto s : ssum)
    {
        sum.push_back(s);
    }
    sort(sum.begin(), sum.end());
    // build a segment tree using the sorted sums
    root = build(sum, 0, sum.size() - 1);
    // next count the number of sums based on low + sum[j] <= sum[i] <= high + sum[j], i > j
    int count = 0;
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        modify(root, tmpSum);
        tmpSum -= nums[i];
        count += query(root, lower + tmpSum, upper + tmpSum);
    }
    return count;
}

#endif