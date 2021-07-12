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

    unsigned int get() const
    {
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        return m_value;
    }

    void increment()
    {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        ++m_value;
    }

    void reset()
    {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        m_value = 0;
    }

    private:
    mutable std::shared_mutex   m_mutex;
    unsigned int                m_value;
};

