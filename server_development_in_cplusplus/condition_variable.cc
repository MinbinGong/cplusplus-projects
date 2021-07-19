#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <iostream>

class Task
{
    int task_id;
public:
    Task(int id) : task_id(id) {}

    void do_task()
    {
        std::cout << "Handle a task, task id: " << task_id
                  << ", thread id: " << std::this_thread::get_id()
                  << std::endl;
    }
};

std::mutex my_mutex;
std::list<Task*> tasks;
std::condition_variable my_cv;

void *consume_thread()
{
    Task *p_task = nullptr;
    while (true)
    {
        std::unique_lock<std::mutex> guard(my_mutex);
        while (tasks.empty())
        {
            mycv.wait(guard);
        }
        p_task = tasks.front();
        tasks.pop_front();

        if (p_task == nullptr)
        {
            continue;
        }
        
        p_task->do_task();
        delete p_task;
        p_task = nullptr;
    }
    return nullptr;
}

void* produce_thread()
{
    int id = 0;
    Task *p_task = nullptr;

    while (true)
    {
        p_task = new Task(id);
        {
            std::lock_guard<std::mutex> guard(my_mutex);
            tasks.push_back(p_task);
            std::cout << "Produce a task, task id: " << id << ", thread id: "
                      << std::this_thread::get_id() << std::endl;
        }

        my_cv.notify_one();
        ++id;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return nullptr;
}

int main()
{
    std::thread consumer1(consume_thread);
    std::thread consumer2(consume_thread);
    std::thread consumer3(consume_thread);
    std::thread consumer4(consume_thread);
    std::thread consumer5(consume_thread);
    
    std::thread producer(produce_thread);

    producer.join();
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
    consumer5.join();

    return 0;
}