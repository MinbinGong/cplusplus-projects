#include <iostream>
#include "CircularContainer.h"
using namespace std;

int main()
{
    CircularContainer<int> cbuf(5);

    cbuf.push(1);
    cbuf.push(2);
    cbuf.push(3);

    auto item = cbuf.pop();
    cbuf.push(4);
    cbuf.push(5);
    cbuf.push(6);

    cbuf.push(7);
    cbuf.push(8);

    item = cbuf.pop();
    item = cbuf.pop();
    item = cbuf.pop();

    item = cbuf.pop();
    item = cbuf.pop();

    cbuf.push(9);

    return 0;
}