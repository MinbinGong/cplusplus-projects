#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

void print(int elem)
{
    cout << elem << ' ';
}

int square(int value)
{
    return value * value;
}

int main()
{
    set<int> coll1;
    vector<int> coll2;

    for (size_t i = 1; i <= 9; i++)
    {
        coll1.insert(i);
    }

    transform(coll1.cbegin(), coll1.cend(), back_inserter(coll2), square);

    return 0;
}