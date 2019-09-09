#ifndef DOUBLE_BUFFER_HPP
#define DOUBLE_BUFFER_HPP

#include <vector>
#include <mutex>
#include <algorithm>

template <typename T>
class double_buffer
{
    typedef T value_type;
    typedef T &reference;
    typedef T const &const_reference;
    typedef T *pointer;

public:
    explicit double_buffer(size_t const size) : rdbuf(size), wrbuf(size) {}

    size_t size() const noexcept { return rdbuf.size(); }

    void write(T const *const str, size_t const size)
    {
        std::unique_lock<std::mutex> lock(mt);
        auto length = std::min(size, wrbuf.size());
        std::copy(ptr, ptr + length, std::begin(wrbuf));
        wrbuf.swap(rdbuf);
    }

    template <class Output>
    void read(Output it) const
    {
        std::unique_lock<std::mutex> lock(mt);
        std::copy(std::cbegin(rdbuf), std::cend(rdbuf), it);
    }

    pointer data() const
    {
        std::unique_lock<std::mutex> lock(mt);
        return rdbuf.data();
    }

    reference operator[](size_t const pos)
    {
        std::unique_lock<std::mutex> lock(mt);
        return rdbuf[pos];
    }

    const_reference operator[](size_t const pos) const
    {
        std::unique_lock<std::mutex> lock(mt);
        return rdbuf[pos];
    }

    void swap(double_buffer other)
    {
        std::swap(rdbuf, other.rdbuf);
        std::swap(wrbuf, other.wrbuf);
    }

private:
    std::vector<T> rdbuf;
    std::vector<T> wrbuf;
    mutable std::mutex mt;
}

#endif