#include <thread>
#include <queue>
#include <vector>
#include <algorithm>
#include <random>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <array>
#include <string>
#include <mutex>

class logger
{
private:
    std::mutex mt;

protected:
    logger(){};

public:
    static logger &instance()
    {
        static logger lg;
        return lg;
    }

    logger(logger const &) = delete;
    logger &operator=(logger const &) = delete;

    void log(std::string_view message)
    {
        std::lock_guard<std::mutex> lock(mt);
        std::cout << "LOG:" << message << std::endl;
    }
};

class ticketing_machine
{
public:
    ticketing_machine(int const start) : last_ticket(start), first_ticket(start) {}

    int next() { return last_ticket++; }
    int last() const { return last_ticket - 1; }
    void reset() { last_ticket = first_ticket; }

private:
    int first_ticket = INT_MIN;
    int last_ticket = INT_MIN;
};

class customer
{
private:
    int number = INT_MIN;

    friend bool operator<(customer const &l, customer const &r);

public:
    customer(int const no) : number(no) {}

    int ticket_number() const noexcept { return number; }
};

bool operator<(customer const &l, customer const &r)
{
    return l.number < r.number;
}

int main()
{
    std::priority_queue<customer> customers;
    bool office_open = true;
    std::mutex mt;
    std::condition_variable cv;

    std::vector<std::thread> desks;
    for (size_t i = 0; i < 3; i++)
    {
        desks.emplace_back([i, &office_open, &mt, &cv, &customers]()
                           { std::random_device rd;
                           auto seed_data = std::array<int, std::mt19937::state_size>{};
                           std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
                           std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
                           std::mt19937 eng(seq);
                           std::uniform_int_distribution<> ud(2000, 3000);
                           logger::instance().log("desk " + std::to_string(i+1) + "open");
                           
                           while (office_open || !customers.empty())
                           {
                               std::unique_lock<std::mutex> locker(mt);
                               cv.wait_for(locker, std::chrono::seconds(1), [&customers]()
                                           { return !customers.empty(); });

                                           if (!customers.empty())
                                           {
                                               auto const c = customers.top();
                                               customers.pop();

                                               logger::instance().log("[-] desk " + std::to_string(i + 1) + " handling customer " + std::to_string(c.ticket_number()));

                                               logger::instance().log("[=] queue size: " + std::to_string(customers.size()));

                                               locker.unlock();
                                               cv.notify_one();

                                               std::this_thread::sleep_for(std::chrono::milliseconds(ud(eng)));

                                               logger::instance().log("[ ] desk " + std::to_string(i + 1) + " done with customer " + std::to_string(c.ticket_number()));
                                           }
                           }
                           logger::instance().log("desk " + std::to_string(i+1) + " closed"); });
    }

    std::thread store([&office_open, &customers, &mt, &cv]()
                      { 
                        ticketing_machine tm(100);

                        std::random_device rd;
                        auto seed_data = std::array<int, std::mt19937::state_size>{};
                        std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
                        std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
                        std::mt19937 eng(seq);
                        std::uniform_int_distribution<> ud(200,300);
                        
                        for (size_t i = 0; i <= 25; i++)
                        {
                            customer c(tm.next());
                            customers.push(c);

                            logger::instance().log("[+] new customer with ticket " + std::to_string(c.ticket_number()));
                            logger::instance().log("[=] queue size: " + std::to_string(customers.size()));

                            cv.notify_one();
                            std::this_thread::sleep_for(std::chrono::milliseconds(ud(eng)));
                        }

                        office_open = false; });
    store.join();
    for (auto &desk : desks)
    {
        desk.join();
    }
}
