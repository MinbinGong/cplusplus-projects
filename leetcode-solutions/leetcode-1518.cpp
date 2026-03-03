/**
 * 1518. Water Bottles
 * 
 * Given numBottles full water bottles, you can exchange numExchange empty water bottles for one full water bottle.
 * The operation of drinking a full water bottle turns it into an empty bottle.
 * Return the maximum number of water bottles you can drink.
 * 
 * Example 1:
 * Input: numBottles = 9, numExchange = 3
 * Output: 13
 * Explanation: You can exchange 3 empty bottles to get 1 full water bottle.
 * Number of water bottles you can drink: 9 + 3 + 1 = 13.
 * 
 * Example 2:
 * Input: numBottles = 15, numExchange = 4
 * Output: 19
 * Explanation: You can exchange 4 empty bottles to get 1 full water bottle.
 * Number of water bottles you can drink: 15 + 3 + 1 = 19.
 * 
 * Example 3:
 * Input: numBottles = 5, numExchange = 5
 * Output: 6
 * Explanation: You can exchange 5 empty bottles to get 1 full water bottle.
 * Number of water bottles you can drink: 5 + 1 = 6.
 * 
 * Note:
 * 1 <= numBottles <= 100
 * 2 <= numExchange <= 100
 * 
 */
class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        // 如果 numExchange 为 1，每次用一个空瓶换一瓶，可以无限换，但题目要求整数，返回一个较大的数
        if (numExchange == 1) {
            // 理论上可以喝无限瓶，但题目可能不会出现这种情况，这里返回一个足够大的数
            return 1000000000;
        }
        // 使用公式计算
        return numBottles + (numBottles - 1) / (numExchange - 1);
    }
};