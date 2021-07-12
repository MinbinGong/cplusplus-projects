#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

#define READER_THREAD_COUNT     (8)
#define LOOP_COUNT              (5000000)

class shared_mutex_counter
{
public:
    shared_mutex_counter() = default;
    ~shared_mutex_counter() = default;

    unsigned int
};