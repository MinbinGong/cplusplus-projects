#include <vector>

template <typename T>
class RingBuffer
{
private:
    std::vector<T> mVec;
    std::vector<T>::iterator mIndex;

public:
    RingBuffer() = default;
    RingBuffer(const std::vector<T> src) : mVec(src), mIndex(mVec.begin()) {}
    ~RingBuffer();

    RingBuffer(const RingBuffer& src) = delete;
    RingBuffer& operator=(const RingBuffer& rhs) = delete;

public:
    T get();
    void insert(const T& src);
};