#ifndef _SKIP_LIST_HPP_
#define _SKIP_LIST_HPP_

const int maxLevel = 4;

template <class T>
class SkipListNode {
 public:
  SkipListNode(){};
  ~SkipListNode(){};

  T key;
  SkipListNode **next;
};

template <class T>
class SkipList {
 public:
  SkipList();

  bool isEmpty() const;
  void choosePowers();
  int chooseLevel();
  T *skipListSearch(const T &);
  void skipListInsert(const T &);

 private:
  typedef SkipListNode<T> *nodePtr;
  nodePtr root[maxLevel];
  int powers[maxLevel];
};

template <class T>
SkipList<T>::SkipList() {
  for (int i = 0; i < maxLevel; i++) {
    root[i] = nullptr;
  }
}

template <class T>
bool SkipList<T>::isEmpty() const {
  return root[0] == nullptr;
}

template <class T>
void SkipList<T>::choosePowers() {
  powers[maxLevel - 1] = (2 << (maxLevel - 1)) - 1;
  for (int i = maxLevel - 2, j = 0; i >= 0; i--, j++) {
    powers[i] = powers[i + 1] - (2 << j);
  }
}

template <class T>
int SkipList<T>::chooseLevel() {
  int i, r = rand() & powers[maxLevel - 1] + 1;

  for (i = 1; i < maxLevel; i++) {
    if (r < powers[i]) {
      return i - 1;
    }
  }

  return i - 1;
}

template <class T>
T *SkipList<T>::skipListSearch(const T &key) {
  if (isEmpty()) {
    return nullptr;
  }

  nodePtr prev, curr;
  int lvl;
  for (lvl = maxLevel - 1; lvl >= 0 && !root[lvl]; lvl--) {
    ;
  }

  prev = curr = root[lvl];
  while (true) {
    if (key == curr->key) {
      return &curr->key;
    } else if (key < curr->key) {
      if (lvl == 0) {
        return nullptr;
      } else if (curr == root[lvl]) {
        curr = root[--lvl];
      } else {
        curr = *(prev->next + --lvl);
      }
    } else {
      prev = curr;
      if (*(curr->next + lvl) != 0) {
        curr = *(curr->next + lvl);
      } else {
        for (lvl--; lvl >= 0 && *(curr->next + lvl) == 0; lvl--) {
          ;
        }

        if (lvl >= 0) {
          curr = *(curr->next + lvl);
        } else {
          return nullptr;
        }
      }
    }
  }
}

template <class T>
void SkipList<T>::skipListInsert(const T &key) {
  nodePtr cur[maxLevel], prev[maxLevel], newNode;
  int lvl, i;
  cur[maxLevel - 1] = root[maxLevel - 1];
  prev[maxLevel - 1] = nullptr;
  for (lvl = maxLevel - 1; lvl >= 0; lvl--) {
    while (cur[lvl] && cur[lvl]->key < key) {
      prev[lvl] = cur[lvl];
      cur[lvl] = *(cur[lvl]->next + lvl);
    }

    if (cur[lvl] && cur[lvl]->key == key) {
      return;
    }

    if (lvl > 0) {
      if (prev[lvl] == nullptr) {
        cur[lvl]-1] = root[lvl-1];
        prev[lvl - 1] = nullptr;
      } else {
        cur[lvl - 1] = *(prev[lvl]->next + lvl - 1);
        prev[lvl - 1] = prev[lvl];
      }
    }
  }

  lvl = chooseLevel();
  newNode = new SkipListNode<T>;
  newNode->next = new nodePtr[sizeof(nodePtr) * (lvl + 1)];
  newNode->key = key;
  for (i = 0; i <= lvl; i++) {
    *(newNode->next + i) = cur[i];
    if (prev[i] == nullptr) {
      root[i] = newNode;
    } else {
      *(prev[i]->next + i) = newNode;
    }
  }
}
#endif  // _SKIP_LIST_HPP_