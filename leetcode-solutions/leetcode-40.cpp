/*
 * Given a collection of candidate numbers (candidates) and a target number
 * (target), find all unique combinations in candidates where the candidate
 * numbers sum to target.
 *
 * Each number in candidates may only be used once in the combination.
 *
 * Note: The solution set must not contain duplicate combinations.
 *
 * Example 1:
 * Input: candidates = [10,1,2,7,6,1,5], target = 8
 * Output:
 * [
 * [1,1,6],
 * [1,2,5],
 * [1,7],
 * [2,6]
 * ]
 *
 * Example 2:
 * Input: candidates = [2,5,2,1,2], target = 5
 * Output:
 * [
 * [1,2,2],
 * [5]
 * ]
 *
 * Constraints:
 * 1 <= candidates.length <= 100
 * 1 <= candidates[i] <= 50
 * 1 <= target <= 30
 */
#include <algorithm>
#include <vector>
using namespace std;

void combinationSumRec(vector<int>& candidates, int target, int begin, vector<vector<int>>& result, vector<int>& t) {
    if (target == 0) {
        result.push_back(t);
        return;
    }

    int x = begin;
    while (begin < candidates.size() && target - candidates[begin] >= 0) {
        if (begin > x && candidates[begin] == candidates[begin - 1]) {
            begin++;
            continue;
        }

        t.push_back(candidates[begin]);

        combinationSumRec(candidates, target - candidates[begin], begin + 1, result, t);

        t.pop_back();
        begin++;
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> t;

    sort(candidates.begin(), candidates.end());

    combinationSumRec(candidates, target, 0, result, t);

    return result;
}
