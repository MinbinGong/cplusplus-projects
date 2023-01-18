#include <vector>
#include <mutex>
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename T>
class double_buffer
{
    using value_type = T;
    using reference = T &;
    using const_reference = T const &;
    using pointer = T *;

public:
    explicit double_buffer(size_t const size) : rdbuf(size), wrbuf(size) {}

    size_t size() const noexcept { return rdbuf.size(); }

    void write(T const *const ptr, size_t const_size)
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
};

template <typename T>
void print_buffer(double_buffer<T> const &buf)
{
    buf.read(std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
}
