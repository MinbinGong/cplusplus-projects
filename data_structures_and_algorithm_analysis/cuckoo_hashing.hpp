#ifndef CUCKOO_HASHING_HPP
#define CUCKOO_HASHING_HPP

#include <vector>

template <typename AnyType>
class CuckooHashFamily
{
public:
    size_t hash(const AnyType &x, int which) const;
    int getNumberOfFunctions();
    void generateFunctions();
};

template <typename AnyType, typename HashFamily>
class CuckooHashTable
{
public:
    explicit CuckooHashFamily(int size = 101) : array(nextPrime(size))
    {
        numHashFunctions = hashFunctions.getNumberOfFunctions();
        rehashes = 0;
        makeEmpty();
    }

    void makeEmpty()
    {
        currentSize = 0;
        for (auto &entry : array)
            entry.isActive = false;
    }
    bool contains(const AnyType &x) const
    {
        return findPos(x) != -1;
    }

    bool remove(const AnyType &x)
    {
        int currentPos = findPos(x);
        if (!isActive(currentPos))
        {
            return false;
        }

        array[currentPos].isActive = false;
        --currentSize;
        return true;
    }
    bool insert(const AnyType &x)
    {
        if (contains(x))
        {
            return false;
        }

        if (currentSize >= array.size() * MAX_LOAD)
            expand();

        return insertHelper1(x);
    }
    bool insert(AnyType &&x)
    {
    }

private:
    struct HashEntry
    {
        AnyType element;
        bool isActive;
        HashEntry(const AnyType &e = AnyType(), bool a = false)
            : element{e}, isActive{a} {}
        HashEntry(AnyType &&e, bool a = false)
            : element{std::move(e)}, isActive{a} {}
    };

    bool insertHelper1(const AnyType &xx)
    {
        const int COUNT_LIMIT = 100;
        AnyType x = xx;

        while (true)
        {
            int lastPos = -1;
            int pos;

            for (int count = 0; count < COUNT_LIMIT; count++)
            {
                for (int i = 0; i < numHashFunctions; i++)
                {
                    pos = myhash(x, i);

                    if (!isActive(pos))
                    {
                        array[pos] = std::move(HashEntry{std::move(x), true});
                        ++currentSize;
                        return true;
                    }
                }
                int i = 0;
                do
                {
                    pos = myhash(x, r.nextInt(numHashFunctions));
                } while (pos == lastPos && i++ < 5);

                lastPos = pos;
                std::swap(x, array[pos].element);
            }
        }
    }
