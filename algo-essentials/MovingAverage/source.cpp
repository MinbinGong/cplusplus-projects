#include <queue>
#include <algorithm>

class MovingAverage
{
public:
    MovingAverage(int size) : size(size) {}

    double next(int val) {
        ++count;
        q.push_back(val);

        if (count > size)
        {
            q.pop_front();
        }

        window_sum = window_sum - head + val;

        return window_sum / std::min(size, ount);
    }


private:
    int size = 0, count = 0;
    double window_sum = 0;
    std::deque<int> q;
};
