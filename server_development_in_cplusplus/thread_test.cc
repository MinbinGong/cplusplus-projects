#include <thread>
#include <iostream>
#include <sstream>

void worker_thread_func()
{
    while (true)
    {
        // do nothing here
    }
}

int main()
{
    std::thread t(worker_thread_func);

    std::thread::id worker_thread_id = t.get_id();
    std::cout << "worker thread id: " << worker_thread_id << std::endl;

    std::thread::id main_thread_id = std::this_thread::get_id();
    std::ostringstream oss;
    oss << main_thread_id;
    std::string str = oss.str();
    std::cout << "main thread id: " << str << std::endl;

    unsigned long long thread_id = std::stoull(str);
    std::cout << "main thread id: " << thread_id << std::endl;

    while(true)
    {
        // do nothing
    }

    return 0;
}