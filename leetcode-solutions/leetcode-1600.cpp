/*
 * 1600. Throne Inheritance
 *
 * A kingdom consists of a king, his children, his grandchildren, and so on. Every once in a while, someone in the family dies or a child is born.
 *
 * The kingdom has a well-defined order of inheritance that consists of the king as the first member. Let's define the recursive function Successor(x, curOrder), which given a person x and the inheritance order so far, returns who should be the next person after x in the order of inheritance.
 *
 * Successor(x, curOrder):
 * if x has no children or all of x's children are in curOrder:
 *     if x is the king return null
 *     else return Successor(x's parent, curOrder)
 * else return x's oldest child who's not in curOrder
 * For example, assume we have a kingdom that consists of the king, his children Alice and Bob (Alice is older than Bob), and finally Alice's son Jack.
 *
 * In the beginning, curOrder will be ["king"].
 * 
 * Successor(king, curOrder) = "king"
 * Successor(Alice, curOrder) = "Bob"
 * Successor(Bob, curOrder) = "Jack"
 * Successor(Jack, curOrder) = null
 * Successor(king, curOrder) = "king"
 * 
 * Constraints:
 * 1 <= kingName.length, curOrder.length <= 15
 * kingName and curOrder[i] consist of lowercase English letters only.
 * All the values of curOrder are unique.
 * The person named kingName will exist in curOrder.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class ThroneInheritance {
private:
    unordered_map<string, vector<string>> children;
    unordered_set<string> dead;
    string kingName;

    void dfs(const string& name, vector<string>& order) {
        if (dead.find(name) == dead.end()) {
            order.push_back(name);
        }
        for (const string& child : children[name]) {
            dfs(child, order);
        }
    }

public:
    ThroneInheritance(string kingName) : kingName(kingName) {}

    void birth(string parentName, string childName) {
        children[parentName].push_back(childName);
    }

    void death(string name) {
        dead.insert(name);
    }

    vector<string> getInheritanceOrder() {
        vector<string> order;
        dfs(kingName, order);
        return order;
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */