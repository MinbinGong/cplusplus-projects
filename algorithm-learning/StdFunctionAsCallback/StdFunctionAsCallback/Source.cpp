#include <iostream>
#include <functional>
using namespace std;

class A
{
private:
    std::function<void()> mCallback;
public:
    A(const std::function<void()> &f)
        : mCallback(f)
    {}

    void notify(void)
    {
        mCallback();
    }
};

class Foo
{
public:
    void operator()(void)
    {
        cout << __FUNCTION__ << endl;
    }
};

int main(void)
{
    Foo foo;
    A aa(foo);
    aa.notify();

    return 0;
}