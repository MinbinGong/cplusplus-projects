#include <iostream>
#include <functional>
#include <type_traits>
using namespace std;

template <typename T>
class Task;

template <typename R, typename...Args>
class Task<R(Args...)>
{
private:
    std::function<R(Args...)> m_fn;

public:
    Task(std::function<R(Args...)> &&f) : m_fn(std::move(f)) {}
    Task(std::function<R(Args...)> &f) : m_fn(f) {}

    R run(Args&&... args)
    {
        return m_fn(std::forward<Args>(args)...); // perfect forward
    }

    template <typename F>
    auto then(F&& f)->Task<typename std::result_of<F(R)>::type(Args...)>
    {
        using return_type = typename std::result_of<F(R)>::type;

        auto func = std::move(m_fn);
        return Task < return_type(Args...)>([func, f](Args&&... args) {
            return f(func(std::forward<Args>(args)...));
        });
    }
};

void TestTask()
{
    Task<int(int)> task([](int i) {return i; });
    auto result = task.then([](int i) {
        return i + 1;
    }).then([](int i) {
        return i + 2;
    }).then([](int i) {
        return i + 3;
    }).run(1);

    cout << result << endl;
}

int main()
{
    TestTask();

    return 0;
}