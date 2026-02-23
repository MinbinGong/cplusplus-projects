/*
 * Number of Atoms
 *
 * Given a chemical formula (given as a string), return the count of each atom.
 * 
 * An atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.
 * 
 * 1 or more digits representing the count of that element may follow if the count is greater than 1. If the count is 1, no digits will follow. For example, H2O and H2O2 are possible, but H1O2 is impossible.
 * 
 * Two atoms with the same name are always adjacent to each other. For example, H2O2 is possible, but H2O is impossible.
 * 
 * Note that the count of an element is the sum of all the counts of the atoms in that element.
 * 
 * Example 1:
 * 
 * Input: formula = "H2O"
 * Output: "H2O"
 * Explanation: The count of atoms is {'H': 2, 'O': 1}.
 * 
 * Example 2:
 * 
 * Input: formula = "Mg(OH)2"
 * Output: "H2MgO2"
 * Explanation: The count of atoms is {'H': 2, 'Mg': 1, 'O': 2}.
 * 
 * Example 3:
 * 
 * Input: formula = "K4(ON(SO3)2)2"
 * Output: "K4N2O14S4"
 * Explanation: The count of atoms is {'K': 4, 'N': 2, 'O': 14, 'S': 4}.
 * 
 * Note:
 * 1. All atom names consist of lowercase letters, except for the first character which is uppercase.
 * 2. The length of formula will be in the range [1, 1000].
 * 3. formula will only consist of letters, digits, and round parentheses, and is a valid formula as defined in the problem.
 * 
 */
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string countOfAtoms(string formula) {
        int n = formula.size();
        // Stack of maps: each map represents counts in a nested scope
        stack<unordered_map<string, int>> st;
        st.push({}); // global scope

        int i = 0;
        while (i < n) {
            if (formula[i] == '(') {
                // Start a new nested scope
                st.push({});
                i++;
            }
            else if (formula[i] == ')') {
                // End of a scope
                i++;
                // Read the multiplier after ')', default 1
                int multiplier = 0;
                while (i < n && isdigit(formula[i])) {
                    multiplier = multiplier * 10 + (formula[i] - '0');
                    i++;
                }
                if (multiplier == 0) multiplier = 1;

                // Pop the current scope, multiply its counts, and merge into the parent scope
                auto curMap = st.top();
                st.pop();
                for (auto& [atom, cnt] : curMap) {
                    st.top()[atom] += cnt * multiplier;
                }
            }
            else {
                // Parse an atom name: starts with uppercase, then optional lowercase
                string atom;
                atom += formula[i++];
                while (i < n && islower(formula[i])) {
                    atom += formula[i++];
                }

                // Parse the number after the atom, default 1
                int cnt = 0;
                while (i < n && isdigit(formula[i])) {
                    cnt = cnt * 10 + (formula[i] - '0');
                    i++;
                }
                if (cnt == 0) cnt = 1;

                // Add to the current scope
                st.top()[atom] += cnt;
            }
        }

        // After processing, the stack contains a single map with all counts
        auto& counts = st.top();

        // Sort atoms lexicographically
        vector<pair<string, int>> elements(counts.begin(), counts.end());
        sort(elements.begin(), elements.end());

        // Build result string
        string result;
        for (auto& [atom, cnt] : elements) {
            result += atom;
            if (cnt > 1) result += to_string(cnt);
        }
        return result;
    }
};