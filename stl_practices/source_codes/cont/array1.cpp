#include <array>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <iostream>
using namespace std;

int main()
{
    array<int, 10> a{11, 22, 33, 44};
    copy(a.cbegin(), a.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;

    a.back() = 99999;
    a[a.size() - 2] = 42;
    copy(a.cbegin(), a.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "sum: " << accumulate(a.begin(), a.end(), 0) << endl;

    transform(a.begin(), a.end(), a.begin(), negate<int>());
    copy(a.cbegin(), a.cend(), ostream_iterator<int>(cout, " "));

    return 0;
}