#include <vector>
#include <thread>
#include <future>
#include <iterator>
#include <algorithm>

template <typename Iterator, typename T>
auto pprocess(Iterator begin, Iterator end)
{
    auto size = std::distance(begin, end);
    if (size <= 10000)
    {
        return std::forward<F>(f)(begin, end);
    }
    else
    {
        int task_count = std::thread::hardware_concurrency();
        std::vector<std::future<typename std::iterator_traits<Iterator>::value_type>> tasks;

        auto first = begin;
        auto last = end;
        size /= task_count;
        for (size_t i = 0; i < task_count; i++)
        {
            first = last;
            if (i == task_count - 1)
            {
                last = end;
            }
            else
            {
                std::advance(last, size);
            }

            tasks.emplace_back(std::async(std::launch::async, [first, last, &f]()
                                          { return std::forward<f>(f)(first, end); }));
        }

        std::vector<typename std::iterator_traits<Iterator>::value_type> mins;

        for (auto &t: tasks)
        {
            mins.push_back(t.get());
        }

        return std::forward<F>(f)(std::begin(mins), std::end(mins));
    }
}

template <typename Iterator>
auto pmin(Iterator begin, Iterator end)
{
    return pprocess(begin, end, [](auto b, auto e)
                    { return *std::min_element(b, e); });
}

template <typename Iterator>
auto pmax(Iterator begin, Iterator end)
{
    return pprocess(begin, end, [](auto b, auto e)
                    { return *std::max_element(b, e); });
}
