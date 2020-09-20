#include <vector>
using namespace std;

int numberOfArithmeticSlices1(vector<int> &A)
{
    int i, n = A.size(), res = 0, cur = 1;
    for (i = 2; i < n; i++)
    {
        if (A[i] - A[i - 1] == A[i - 1] - A[i - 2])
        {
            cur++;
        }
        else
        {
            res = res + (cur * (cur - 1)) / 2;
            cur = 1;
        }
    }
    res = res + (cur * (cur - 1)) / 2;
    return res;
}

int numberOfArithmeticSlices2(vector<int> &A)
{
    if (A.size() < 3)
        return 0;
    int result = 0;
    vector<int> currentElements;
    int currentDifference = A[1] - A[0];
    currentElements.push_back(A[1] - A[0]);
    for (int i = 1; i < A.size(); i++)
    {
        if (A[i] - A[i - 1] == currentDifference)
        {
            currentElements.push_back(A[i - 1]);
            if (currentElements.size() >= 3)
            {
                result += currentElements.size() - 2;
            }
        }
        else
        {
            currentElements.clear();
            currentDifference = A[i] - A[i - 1];
            currentElements.push_back(A[i - 1]);
            currentElements.push_back(A[i]);
        }
    }

    return result;
}
