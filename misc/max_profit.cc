#include <iostream>
#include <vector>

int maxProfit(std::vector<int> &prices) {
    int buy = prices[0], max_profit = 0;
    for (int i = 1; i < prices.size(); ++i) {
        if (buy > prices[i]) {
            buy = prices[i];
        } else if (prices[i] - buy > max_profit) {
            max_profit = prices[i] - buy;
        }
    }
    return max_profit;
}

int main() {
    std::vector<int> prices{7, 1, 5, 6, 4};
    int max_profit = maxProfit(prices);
    std::cout << max_profit << std::endl;
    return 0;
}