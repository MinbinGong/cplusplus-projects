#ifndef _SKIP_LIST_HPP_
#define _SKIP_LIST_HPP_

const int maxLevel = 4;

template <class T>
class SkipListNode
{
public:
  SkipListNode () {};
  ~SkipListNode () {};

  T key;
  SkipListNode **next;
};



#endif // _SKIP_LIST_HPP_