#include <chrono>
#include

inline int number_of_days(int const y1, unsigned int const m1, unsigned int const d1,
                          int const y2, unsigned int const m2, unsigned int const d2)
{
    return (date::sys_days{year{y1} / month{m1} / day{d1}} - date::sys_days{year{y2} / month{m2} / day{d2}}).count();
}

inline int number_of_days(date::sys_days const &first, date::sys_days const &last)
{
    return (last - first).count;
}
