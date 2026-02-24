/*
 * Reveal Cards In Increasing Order
 *
 * In a deck of cards, every card has a unique integer.  You can order the deck in any order you want.
 *
 * Initially, all the cards start face down (unrevealed) in one deck.
 *
 * Now, you do the following steps repeatedly, until all cards are revealed:
 *
 * Take the top card of the deck, reveal it, and take it out of the deck.
 * If there are still cards in the deck, put the next top card of the deck at the bottom of the deck.
 * If there are still unrevealed cards, go back to step 1.  Otherwise, stop.
 * Return an ordering of the deck that would reveal the cards in increasing order.
 *
 * The first entry in the answer is considered to be the top of the deck.
 *
 * Example 1:
 * Input: [17,13,11,2,3,5,7]
 * Output: [2,13,3,11,5,17,7]
 * Explanation:
 * We get the deck in the order [17,13,11,2,3,5,7] (this order doesn't matter), and reorder it.
 * After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of the deck.
 * We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
 * We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
 * We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
 * We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
 * We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
 * We reveal 13, and move 17 to the bottom.  The deck is now [17].
 * We reveal 17.
 * Since all the cards revealed are in increasing order, the answer is correct.
 * 
 * Note:
 * 1 <= A.length <= 1000
 * 1 <= A[i] <= 10^6
 * A[i] != A[j] for all i != j
 * 
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int n = deck.size();
        sort(deck.begin(), deck.end());          // 将牌按升序排列
        queue<int> q;
        for (int i = 0; i < n; ++i) q.push(i);  // 队列保存原始顺序中的位置索引
        
        vector<int> result(n);
        for (int card : deck) {                  // 按升序依次放置牌
            result[q.front()] = card;            // 将当前最小牌放到队首对应的位置
            q.pop();                              // 该位置已使用，移除
            if (!q.empty()) {                      // 将下一张牌移到队尾（模拟操作）
                q.push(q.front());
                q.pop();
            }
        }
        return result;
    }
};