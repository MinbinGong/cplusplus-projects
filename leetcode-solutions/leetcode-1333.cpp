/*
 * 1333. Filter Restaurants by Vegan-Friendly, Price and Distance
 *
 * Given the array restaurants where  restaurants[i] = [idi, ratingi, veganFriendlyi, pricei, distancei]. You have to filter the restaurants using three filters.
 *
 * The veganFriendly filter will be either true (meaning you should only include restaurants with veganFriendlyi set to true) or false (meaning you can include any restaurant). In addition, you have the filters maxPrice and maxDistance which are the maximum value for price and distance of restaurants you should consider respectively.
 *
 * Return the array of restaurant IDs after filtering, ordered by rating from highest to lowest. For restaurants with the same rating, order them by id from highest to lowest. For simplicity veganFriendlyi and veganFriendly take value 1 when it is true, and 0 when it is false.
 *
 * Example 1:
 * Input: restaurants = [[1,4,1,40,10],[2,8,0,50,5],[3,8,1,30,4],[4,10,0,10,3],[5,1,1,15,1]], veganFriendly = 1, maxPrice = 50, maxDistance = 10
 * Output: [3,1,5] 
 * Explanation: 
 * The restaurants are:
 * Restaurant 1 [id=1, rating=4, veganFriendly=1, price=40, distance=10]
 * Restaurant 2 [id=2, rating=8, veganFriendly=0, price=50, distance=5]
 * Restaurant 3 [id=3, rating=8, veganFriendly=1, price=30, distance=4]
 * Restaurant 4 [id=4, rating=10, veganFriendly=0, price=10, distance=3]
 * Restaurant 5 [id=5, rating=1, veganFriendly=1, price=15, distance=1]
 * 
 * Example 2:
 * Input: restaurants = [[1,4,1,40,10],[2,8,0,50,5],[3,8,1,30,4],[4,10,0,10,3],[5,1,1,15,1]], veganFriendly = 0, maxPrice = 50, maxDistance = 10
 * Output: [4,3,2,1,5]
 * Explanation: The restaurants are the same as in example 1, but in this case the filter veganFriendly = 0, therefore all restaurants are considered.
 * 
 * Example 3:
 * Input: restaurants = [[1,4,1,40,10],[2,8,0,50,5],[3,8,1,30,4],[4,10,0,10,3],[5,1,1,15,1]], veganFriendly = 0, maxPrice = 30, maxDistance = 3
 * Output: [4,5]
 * 
 * Note:
 * 1 <= restaurants.length <= 10^4
 * restaurants[i].length == 5
 * 1 <= idi, ratingi, pricei, distancei <= 10^5
 * 1 <= maxPrice, maxDistance <= 10^5
 * veganFriendlyi and veganFriendly are 0 or 1.
 * All idi are distinct.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> filterRestaurants(vector<vector<int>>& restaurants, int veganFriendly, int maxPrice, int maxDistance) {
        // Filter based on criteria
        vector<pair<int, int>> candidates; // (rating, id) for sorting
        for (const auto& r : restaurants) {
            int id = r[0];
            int rating = r[1];
            int vegan = r[2];
            int price = r[3];
            int distance = r[4];
            
            // Check vegan-friendly condition
            if (veganFriendly == 1 && vegan == 0) continue;
            // Check price and distance limits
            if (price > maxPrice || distance > maxDistance) continue;
            
            candidates.emplace_back(rating, id);
        }
        
        // Sort by rating descending, then id descending
        sort(candidates.begin(), candidates.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
            if (a.first != b.first) return a.first > b.first;
            return a.second > b.second;
        });
        
        // Extract ids
        vector<int> result;
        for (const auto& p : candidates) {
            result.push_back(p.second);
        }
        return result;
    }
};