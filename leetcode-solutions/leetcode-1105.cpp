/*
 * 1105. Filling Bookcase Shelves
 * 
 * We have a sequence of books: the i-th book has thickness books[i][0] and height books[i][1].
 * 
 * We want to place these books in order onto bookcase shelves that have total width shelf_width.
 * 
 * We choose some of the books to place on this shelf (such that the sum of their thickness is <= shelf_width), then build another level of the shelf of the bookcase so that the total height of the bookcase has increased by the maximum height of the books we just put down.  We repeat this process until there are no more books to place.
 * 
 * Note again that at each step of the above process, the order of the books we place is the same order as the given sequence of books.  For example, if we have an ordered list of 5 books, we might place the first and second book onto the first shelf, the third book on the second shelf, and the fourth and fifth book on the last shelf.
 * 
 * Return the minimum possible height that the total bookshelf can be after placing shelves in this manner.
 * 
 * 1 <= books.length <= 1000
 * 1 <= books[i][0] <= shelf_width <= 1000
 * 1 <= books[i][1] <= 1000
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        // dp[i] 表示放置前i本书的最小总高度
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;  // 没有书时高度为0
        
        for (int i = 1; i <= n; i++) {
            int currentWidth = 0;
            int maxHeight = 0;
            
            // 尝试将第j本书到第i本书放在同一层
            for (int j = i; j >= 1; j--) {
                // 累加宽度
                currentWidth += books[j - 1][0];
                
                // 如果宽度超过书架宽度，停止尝试
                if (currentWidth > shelfWidth) {
                    break;
                }
                
                // 更新当前层的最大高度
                maxHeight = max(maxHeight, books[j - 1][1]);
                
                // 状态转移：dp[i] = min(dp[i], dp[j-1] + maxHeight)
                dp[i] = min(dp[i], dp[j - 1] + maxHeight);
            }
        }
        
        return dp[n];
    }
};