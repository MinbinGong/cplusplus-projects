#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <list>
#include <vector>

template <typename Key> class hash {
public:
  size_t operator()(const Key &k) const {}
};

template <typename HashedObj> class HashTable {
private:
  struct HashEntry {
    HashedObj element;
    EntryType info;

    HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
        : element{e}, info{i} {}
    HashEntry(HashedObj &&e, EntryType i = EMPTY)
        : element{std::move(e)}, info{i} {}
  };

  std::vector<HashEntry> array;
  int currentSize;

private:
  bool isActive(int currentPos) const {
    return array[currentPos].info == ACTIVE;
  }

  int findPos(const HashedObj &x) const {
    int offset = 1;
    int currentPos = myhash(x);

    while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
      currentPos += offset;
      offset += 2;
      if (currentPos >= array.size()) {
        currentPos -= array.size();
      }
    }
    return currentPos;
  }

  void rehash() {
    std::vector<HashEntry> oldArray = array;

    array.resize(nextPrime(2 * oldArray.size()));
    for (auto &entry : array)
      entry.info = EMPTY;

    currentSize = 0;
    for (auto &entry : oldArray)
      if (entry.info == ACTIVE) {
        insert(std::move(entry.element));
      }
  }

  size_t myhash(const HashedObj &x) const {
    static hash<HashedObj> hf;
    return hf(x) % array.size();
  }

public:
  explicit HashTable(int size = 10) : array(nextPrime(size)) { makeEmpty(); }
  bool contains(const HashedObj &x) const { return isActive(findPos(x)); }

  void makeEmpty() {
    currentSize = 0;
    for (auto &entry : array)
      entry.info = EMPTY;
  }

  bool insert(const HashedObj &x) {
    int currentPos = findPos(x);
    if (isActive(currentPos)) {
      return false;
    }

    array[currentPos].element = x;
    array[currentPos].info = ACTIVE;

    if (++currentSize > array.size()) {
      rehash();
    }
    return true;
  }

  //   bool insert(HashedObj &&x);
  bool remove(const HashedObj &x) {
    int currentPos = findPos(x);

    if (!isActive(currentPos)) {
      return false;
    }
    array[currentPos].info = DELETED;
    return true;
  }

  enum EntryType { ACTIVE, EMPTY, DELETED };
};
#endif