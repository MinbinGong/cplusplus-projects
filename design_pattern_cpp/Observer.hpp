#include "NonCopyable.hpp"
#include <iostream>
#include <string>
#include <functional>
#include <map>

template <typename Func>
class Events : NonCopyable
{
public:
    Events() {}
    ~Events() {}

    int Connect(Func &&f)
    {
        return Assign(f);
    }

    int Connect(const Func &f)
    {
        return Assign(f);
    }

    void Disconnect(int key)
    {
        m_connections.erase(key);
    }

    template <typename... Args>
    void Notify(Args &&... args)
    {
        for (auto &it : m_connections)
        {
            it.second(std::forward<Args>(args)...);
        }
    }

private:
    template <typename F>
    int Assign(F &&f)
    {
        int k = m_observerId++;
        m_connections.emplace(k, std::forward<F>(f));
        return k;
    }

private:
    int m_observerId = 0;
    std::map<int, Func> m_connections;
};