#include <string>
#include <functional>
#include <memory>
#include <map>
#include "NonCopyable.hpp"

namespace
{
const int MaxObjectNum = 10;
}

template <typename T>
class ObjectPool : NonCopyable
{
private:
    std::multimap<std::string, std::shared_ptr<T>> mObjectMap;

private:
    template <typename... Args>
    using Constructor = std::function<std::shared_ptr<T>(Args...)>;

public:
    template <typename... Args>
    void Init(size_t num, Args &&... args)
    {
        if (num <= 0 || num > MaxObjectNum)
        {
            throw std::logic_error("Object number out of range.");
        }

        auto constructName = typeid(Constructor<Args...>).name();
        for (size_t i = 0; i < num; ++i)
        {
            mObjectMap.emplace(constructName,
                               std::shared_ptr<T>(new T(std::forward<Args>(args)...),
                                                  [this, constructName](T *p) {
                                                      mObjectMap.emplace(std::move(constructName), std::shared_ptr<T>(p));
                                                  }));
        }
    }

    template<typename... Args>
    std::shared_ptr<T> Get()
    {
        std::string constructName = typeid(Constructor<Args...>).name();

        auto range = mObjectMap.equal_range(constructName);
        for (auto it = range.first; it != range.second; ++it)
        {
            auto ptr = it->second;
            mObjectMap.erase(it);
            return ptr;
        }
        return nullptr;
    }
};