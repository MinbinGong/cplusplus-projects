/**
 * 1801. Number of Orders in the Backlog
 * 
 * You are given a 2D integer array orders, where each orders[i] = [pricei, amounti, orderTypei] denotes that amounti orders have been placed of type orderTypei at the price pricei. The orderTypei is:
 * 
 * 0 if it is a batch of buy orders, or
 * 1 if it is a batch of sell orders.
 * Note that orders[i] represents a batch of amounti independent orders with the same price and order type. All orders represented by orders[i] will be placed before all orders represented by orders[i+1] for all valid i.
 * 
 * There is a backlog that consists of orders that have not been executed. The backlog is initially empty. When an order is placed, the following happens:
 * 
 * If the order is a buy order, you look at the sell order with the smallest price in the backlog. If that sell order's price is smaller than or equal to the current buy order's price, they will match and be executed, and that sell order will be removed from the backlog. Else, the buy order is added to the backlog.
 * 
 * Vice versa, if the order is a sell order, you look at the buy order with the largest price in the backlog. If that buy order's price is larger than or equal to the current sell order's price, they will match and be executed, and that buy order will be removed from the backlog. Else, the sell order is added to the backlog.
 * 
 * Return the total amount of orders in the backlog after placing all the orders from the input. Since this number can be large, return it modulo 109 + 7.
 * 
 *  
 * 
 * Example 1:
 * 
 * Input: orders = [[10,5,0],[15,2,1],[25,1,1],[30,4,0]]
 * Output: 6
 * Explanation: There are 5 buy orders with prices 10, 15, 25, 30.
 * There are 2 sell orders with prices 15, 25.
 * After the match of the buy order 25 with the sell order 25, sell order 15 with buy order 15, and sell order 10 with buy order 10, there are still 1 buy order (with price 30) in the backlog.
 * Finally, we have 5 orders in the backlog: 1 buy order with price 30, 2 buy orders with price 10, and 2 sell orders with price 15.
 * Example 2:
 * 
 * Input: orders = [[7,1000000000,1],[15,3,0],[5,999999995,0],[5,1,1]]
 * Output: 999999984
 * Explanation: There are 109 buy orders with price 7, 3 sell orders with price 15, and 2 sell orders with price 5.
 * After the match of the buy order 5 with the sell order 5, sell order 15 with buy order 15, and sell order 7 with buy order 7, there are still 3 buy orders with price 5 in the backlog.
 * Finally, we have 999999984 orders in the backlog: 3 buy orders with price 5, 2 buy orders with price 7, and 1 buy order with price 15.
 *  
 * 
 * Constraints:
 * 
 * 1 <= orders.length <= 105
 * orders[i].length == 3
 * 0 <= pricei, amounti <= 109
 * orderTypei is either 0 or 1.
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        const int MOD = 1e9 + 7;

        // Max heap for buy orders (highest price first)
        priority_queue<pair<int, int>> buys;
        // Min heap for sell orders (lowest price first)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> sells;

        for (auto& order : orders) {
            int price = order[0];
            int amount = order[1];
            int type = order[2]; // 0 = buy, 1 = sell

            if (type == 0) { // buy order
                while (amount > 0 && !sells.empty() && sells.top().first <= price) {
                    auto [sellPrice, sellAmount] = sells.top();
                    sells.pop();
                    int matched = min(amount, sellAmount);
                    amount -= matched;
                    sellAmount -= matched;
                    if (sellAmount > 0) {
                        sells.push({sellPrice, sellAmount});
                    }
                }
                if (amount > 0) {
                    buys.push({price, amount});
                }
            } else { // sell order
                while (amount > 0 && !buys.empty() && buys.top().first >= price) {
                    auto [buyPrice, buyAmount] = buys.top();
                    buys.pop();
                    int matched = min(amount, buyAmount);
                    amount -= matched;
                    buyAmount -= matched;
                    if (buyAmount > 0) {
                        buys.push({buyPrice, buyAmount});
                    }
                }
                if (amount > 0) {
                    sells.push({price, amount});
                }
            }
        }

        long long total = 0;
        while (!buys.empty()) {
            total = (total + buys.top().second) % MOD;
            buys.pop();
        }
        while (!sells.empty()) {
            total = (total + sells.top().second) % MOD;
            sells.pop();
        }
        return total;
    }
};
