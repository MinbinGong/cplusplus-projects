#pragma once

#include <vector>

template <typename T>
class CircularContainer
{
    using const_iterator = CircularContainerIterator<T>;

    CircularContainer() = delete;
private:
    std::vector<T> mData;
    size_t mHead = -1;
    size_t mSize = 0;

    size_t next_pos() const noexcept
    {
        return mSize == 0 ? 0 : (mHead + 1) % mData.size();
    }
    size_t first_pos() const noexcept
    {
        return mSize == 0 ? 0 : (mHead + mData.size() - mSize + 1) % mData.size();
    }
    friend class CircularContainerIterator<T>;
public:
    explicit CircularContainer(size_t const size) : mSize(size) {}

    bool clear() noexcept { mHead = -1; mSize = 0; }
    bool empty() const noexcept { return mSize == 0; }
    bool full() const noexcept { return mSize == mData.size(); }
    size_t capacity() const noexcept { return mData.size(); }
    size_t size() const noexcept { return mSize; }

    void push(T const item)
    {
        mHead = next_pos();
        mData[mHead] = item;
        if (mSize < mData.size())
        {
            mSize++;
        }
    }

    T pop()
    {
        if (empty())
        {
            throw std::runtime_error("Empty Container");
        }
        auto pos = first_pos();
        mSize--;
        return mData[pos];
    }

    const_iterator begin() const
    {
        return const_iterator(*this, first_pos(), empty());
    }

    const_iterator end() const
    {
        return const_iterator(*this, next_pos(), true);
    }
};

template <typename T>
class CircularContainerIterator
{
    typedef CircularContainerIterator self_type;
    typedef T value_type;
    typedef T& reference;
    typedef T const& const_reference;
    typedef T* pointer;
    typedef std::random_access_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;
public:
    CircularContainerIterator(CircularContainer<T> const& buf, size_t const pos, bool const last) : mBuffer(buf->mSize), mIndex(pos), mLast(last) {}

    self_type& operator++ ()
    {
        if (mLast)
        {
            throw std::out_of_range("Iterator cannot be incremented past the end of range.");
        }
        mIndex = (mIndex + 1) % mBuffer.mData.size();
        mLast = mIndex = mBuffer.next_pos();
        return *this;
    }

    self_type operator++ (int)
    {
        self_type tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator== (self_type const& other) const
    {
        assert(compatible(other));
        return mIndex == other.mIndex && mLast == other.mLast;
    }

    bool operator!= (self_type const& other) const
    {
        return !(*this == other);
    }

    const_reference operator* () const
    {
        return mBuffer.mData[mIndex];
    }

    const_reference operator->() const
    {
        return mBuffer.mData[mIndex];
    }
private:
    bool compatible(self_type const& other) const
    {
        return &mBuffer == &other.mBuffer;
    }

    CircularContainer<T> const& mBuffer;
    size_t mIndex;
    bool mLast;
};