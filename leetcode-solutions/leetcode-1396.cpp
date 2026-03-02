/**
 * 1396. Design Underground System
 * 
 * Implement the class UndergroundSystem that supports three methods:
 * 
 * 1. checkIn(int id, string stationName, int t)
 * A customer with id card equal to id, gets in the station stationName at time t.
 * A customer can only be checked into one place at a time.
 * 
 * 2. checkOut(int id, string stationName, int t)
 * A customer with id card equal to id, gets out from the station stationName at time t.
 * 
 * 3. getAverageTime(string startStation, string endStation)
 * Returns the average time to travel between the startStation and the endStation.
 * The average time is computed from all the previous traveling from startStation to endStation that happened directly.
 * Call to getAverageTime is always valid.
 * 
 * You can assume all calls to checkIn and checkOut methods are consistent. That is, if a customer gets in at time t1 at some station, then it gets out at time t2 with t2 > t1. All events happen in chronological order.
 * 
 * Example 1:
 * Input
 * ["UndergroundSystem","checkIn","checkIn","checkIn","checkOut","checkOut","checkOut","getAverageTime","getAverageTime","checkIn","getAverageTime","checkOut","getAverageTime"]
 * [[],[45,"Leyton",3],[32,"Paradise",8],[27,"Leyton",10],[45,"Waterloo",15],[27,"Waterloo",20],[32,"Cambridge",22],["Paradise","Cambridge"],["Leyton","Waterloo"],[10,"Leyton",24],["Leyton","Waterloo"],[10,"Waterloo",38],["Leyton","Waterloo"]]
 * Output
 * [null,null,null,null,null,null,null,14.00000,11.00000,null,11.00000,null,12.00000]
 * 
 * Explanation
 * UndergroundSystem undergroundSystem = new UndergroundSystem();
 * undergroundSystem.checkIn(45, "Leyton", 3);
 * 
 * Example 2:
 * Input
 * ["UndergroundSystem","checkIn","checkOut","getAverageTime","checkIn","checkOut","getAverageTime","checkIn","checkOut","getAverageTime"]
 * [[],[10,"Leyton",3],[10,"Paradise",8],["Leyton","Paradise"],[5,"Leyton",10],[5,"Paradise",16],["Leyton","Paradise"],[2,"Leyton",21],[2,"Paradise",30],["Leyton","Paradise"]]
 * Output
 * [null,null,null,5.00000,null,null,5.50000,null,null,6.66667]
 * 
 * Explanation
 * UndergroundSystem undergroundSystem = new UndergroundSystem();
 * undergroundSystem.checkIn(10, "Leyton", 3);
 * undergroundSystem.checkOut(10, "Paradise", 8);
 * undergroundSystem.getAverageTime("Leyton", "Paradise"); // return 5.00000
 * undergroundSystem.checkIn(5, "Leyton", 10);
 * undergroundSystem.checkOut(5, "Paradise", 16);
 * undergroundSystem.getAverageTime("Leyton", "Paradise"); // return 5.50000
 * undergroundSystem.checkIn(2, "Leyton", 21);
 * undergroundSystem.checkOut(2, "Paradise", 30);
 * undergroundSystem.getAverageTime("Leyton", "Paradise"); // return 6.66667
 * 
 * Note:
 * Total number of check-ins and check-outs will be between 1 and 20000.
 * Total number of calls for getAverageTime will be between 1 and 20000.
 * Station names consist of uppercase and lowercase English letters and are length between 1 and 10.
 * Times are given in the format HH:MM, representing the hours and minutes respectively, with integer values in the range [00:00, 23:59].
 * Answers within 10^-5 of the actual value will be accepted as correct.
 * 
 */
#include <unordered_map>
#include <string>
#include <utility>
using namespace std;

class UndergroundSystem {
private:
    // customerId -> {startStation, startTime}
    unordered_map<int, pair<string, int>> checkIns;
    
    // key: startStation + "," + endStation -> {totalTime, count}
    unordered_map<string, pair<double, int>> travelRecords;

public:
    UndergroundSystem() {}
    
    void checkIn(int id, string stationName, int t) {
        checkIns[id] = {stationName, t};
    }
    
    void checkOut(int id, string stationName, int t) {
        auto it = checkIns.find(id);
        string startStation = it->second.first;
        int startTime = it->second.second;
        
        string key = startStation + "," + stationName;
        double travelTime = t - startTime;
        
        travelRecords[key].first += travelTime;
        travelRecords[key].second += 1;
        
        // remove check-in record
        checkIns.erase(it);
    }
    
    double getAverageTime(string startStation, string endStation) {
        string key = startStation + "," + endStation;
        auto& rec = travelRecords[key];
        return rec.first / rec.second;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */