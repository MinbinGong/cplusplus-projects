/**
 * 1418. Display Table of Food Orders in a Restaurant
 * 
 * Given the array orders, which represents the orders that customers have done in a restaurant. More specifically orders[i]=[customerNamei,tableNumberi,foodItemi] where customerNamei is the name of the customer, tableNumberi is the table customer sit at, and foodItemi is the item customer orders.
 * 
 * Return the restaurant's “display table”. The “display table” is a table whose row entries denote how many of each food item each table ordered. The first column is the table number and the remaining columns correspond to each food item in alphabetical order. The first row should be a header whose first column is “Table”, followed by the names of the food items. Note that the customer names are not part of the table. Additionally, the rows should be sorted in numerically increasing order.
 * 
 * Example 1:
 * 
 * Input: orders = [["David","3","Ceviche"],["Corina","10","Beef Burrito"],["David","3","Fried Chicken"],["Carla","5","Water"],["Carla","5","Ceviche"],["Rous","3","Ceviche"]]
 * Output: [["Table","Beef Burrito","Ceviche","Fried Chicken","Water"],["3","0","2","1","0"],["5","0","1","0","1"],["10","1","0","0","0"]] 
 * Explanation:
 * The display table looks like:
 * Table,Beef Burrito,Ceviche,Fried Chicken,Water
 * 3    ,0           ,2      ,1            ,0
 * 5    ,0           ,1      ,0            ,1
 * 10   ,1           ,0      ,0            ,0
 * For the table 3: David orders "Ceviche" and "Fried Chicken", and Rous orders "Ceviche".
 * For the table 5: Carla orders "Water" and "Ceviche".
 * For the table 10: Corina orders "Beef Burrito". 
 * 
 * Example 2:
 * 
 * Input: orders = [["James","12","Fried Chicken"],["Ratesh","12","Fried Chicken"],["Amadeus","12","Fried Chicken"],["Adam","1","Canadian Waffles"],["Brianna","1","Canadian Waffles"]]
 * Output: [["Table","Canadian Waffles","Fried Chicken"],["1","2","0"],["12","0","3"]] 
 * Explanation: 
 * For the table 1: Adam and Brianna order "Canadian Waffles".
 * For the table 12: James, Ratesh and Amadeus order "Fried Chicken".
 * 
 * Note:
 * 1 <= orders.length <= 5 * 10^4
 * orders[i].length == 3
 * 1 <= customerNamei.length, foodItemi.length <= 20
 * customerNamei and foodItemi consist of lowercase and uppercase English letters and the space character.
 * tableNumberi is a valid integer between 1 and 500.
 * 
 */
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;

class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
        // map: table number -> (food item -> count)
        map<int, unordered_map<string, int>> tableMap;
        // set to collect all unique food items
        set<string> foodSet;

        for (const auto& order : orders) {
            int table = stoi(order[1]);          // table number as int
            string food = order[2];               // food item
            tableMap[table][food]++;               // increment count
            foodSet.insert(food);                   // record food
        }

        // sorted list of food items
        vector<string> foods(foodSet.begin(), foodSet.end());

        // build the header row
        vector<vector<string>> result;
        vector<string> header = {"Table"};
        header.insert(header.end(), foods.begin(), foods.end());
        result.push_back(header);

        // build rows for each table (tables are already sorted by map)
        for (const auto& [table, foodCounts] : tableMap) {
            vector<string> row;
            row.push_back(to_string(table));       // table number as string
            for (const string& food : foods) {
                // if food exists for this table, get count, otherwise "0"
                int count = foodCounts.count(food) ? foodCounts.at(food) : 0;
                row.push_back(to_string(count));
            }
            result.push_back(row);
        }

        return result;
    }
};