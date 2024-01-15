#include <iterator>
#include <priority_queue>
#include <set>

// class MedianFinder
//{
// public:
//	void addNum(int num)
//	{
//		numSet.insert(num);
//	}
//
//	double findMedian()
//	{
//		it = numSet.begin();
//		size = numSet.size();
//		std::advance(it, size / 2);
//
//		if (size & 1)
//		{
//			return *it;
//		}
//		else
//		{
//			return (double)(*--it + *++it) / 2.0;
//		}
//	}
// private:
//	std::multiset<int> numSet;
//	std::multiset<int>::iterator it;
//	int size;
// };

class MedianFinder {
  priority_queue<int, vector<int>, less<int> > minQ;
  priority_queue<int, vector<int>, greater<int> > maxQ;

  void rebalanceQueues() {
    if (minQ.size() + 1 < maxQ.size()) {
      minQ.push(maxQ.top());
      maxQ.pop();
    } else if (maxQ.size() + 1 < minQ.size()) {
      maxQ.push(minQ.top());
      minQ.pop();
    }
  }

 public:
  MedianFinder() {}

  void addNum(int num) {
    if (!minQ.empty() && num > minQ.top()) {
      maxQ.push(num);
    } else {
      minQ.push(num);
    }
    rebalanceQueues();
  }

  double findMedian() {
    if (maxQ.empty() && minQ.empty()) return 0.0;
    if (minQ.size() > maxQ.size() || maxQ.empty())
      return minQ.top();
    else if (minQ.size() < maxQ.size() || minQ.empty())
      return maxQ.top();

    return (minQ.top() + maxQ.top()) / 2.0;
  }
};