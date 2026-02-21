/*
 * Sequence Reconstruction
 *
 * Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs. The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104. Reconstruction means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it). Determine whether there is only one sequence that can be reconstructed from seqs and it is the org sequence.
 * 
 * Constraints:
 * 1 <= n <= 104
 * 1 <= seqs.length <= 104
 * 1 <= seqs[i].length <= 104
 * sum(seqs[i].length) <= 105
 * 1 <= seqs[i][j] <= n
 * All the integers in seqs[i] are unique.
 * org is a permutation of {1,2,…,n}.
 * 
 */
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        int n = org.size();
        vector<vector<int>> adj(n + 1);
        vector<int> indeg(n + 1, 0);
        set<pair<int, int>> edges;

        // Build graph from sequences
        for (const auto& seq : seqs) {
            if (seq.empty()) continue;
            for (int num : seq) {
                if (num < 1 || num > n) return false; // number outside org
            }
            for (size_t j = 0; j < seq.size() - 1; ++j) {
                int a = seq[j], b = seq[j + 1];
                if (edges.count({a, b}) == 0) {
                    edges.insert({a, b});
                    adj[a].push_back(b);
                    indeg[b]++;
                }
            }
        }

        // Topological sort with uniqueness check
        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (indeg[i] == 0) q.push(i);
        }

        int idx = 0;
        while (!q.empty()) {
            if (q.size() != 1) return false;   // multiple choices
            int cur = q.front(); q.pop();
            if (idx >= n || cur != org[idx]) return false; // wrong order
            idx++;
            for (int nxt : adj[cur]) {
                indeg[nxt]--;
                if (indeg[nxt] == 0) q.push(nxt);
            }
        }
        return idx == n; // all nodes processed (no cycle)
    }
};