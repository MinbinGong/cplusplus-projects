/*
 * Online Election
 *
 * In an election, the i-th vote was cast for persons[i] at time times[i].
 * 
 * Now, we would like to implement the following query function: TopVotedCandidate.q(int t) will return the number of the person that was leading the election at time t.  
 * 
 * Votes cast at time t will count towards our query.  In the case of a tie, the most recent vote (among tied candidates) wins.
 * 
 * Example 1:
 * Input: ["TopVotedCandidate","q","q","q","q","q","q"], [[[0,1,1,0,0,1,0],[0,5,10,15,20,25,30]],[3],[12],[25],[15],[24],[8]]
 * Output: [null,0,1,1,0,0,1]
 * Explanation: 
 * At time 3, the votes are [0], and 0 is leading.
 * At time 12, the votes are [0,1,1], and 1 is leading.
 * 
 * Note:
 * 1 <= persons.length = times.length <= 5000
 * 0 <= persons[i] <= persons.length
 * times is a strictly increasing array with all elements in [0, 10^9].
 * TopVotedCandidate.q is called at most 10000 times per test case.
 * TopVotedCandidate.q(int t) is always called with t >= times[0].
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class TopVotedCandidate {
private:
    vector<int> leaders; // leader at each vote time
    vector<int> times;   // vote times

public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        this->times = times;
        int n = persons.size();
        unordered_map<int, int> count; // votes per person
        int leader = -1;
        int maxVotes = 0;

        for (int i = 0; i < n; ++i) {
            int p = persons[i];
            count[p]++;
            if (count[p] >= maxVotes) {
                maxVotes = count[p];
                leader = p;
            }
            leaders.push_back(leader);
        }
    }

    int q(int t) {
        // find the largest time <= t
        int idx = upper_bound(times.begin(), times.end(), t) - times.begin() - 1;
        return leaders[idx];
    }
};