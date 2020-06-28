#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
    const int a = 12;
    const int &j = a;

    auto i = j;

    i = 13;

    cout << i << endl;

    return 0;
}