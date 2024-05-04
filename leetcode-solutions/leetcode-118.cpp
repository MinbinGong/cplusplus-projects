/*
 * Pascal's Triangle
 *
 * Given an integer numRows, return the first numRows of Pascal's triangle.
 * In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
 */
#include <vector>
#include <map>
#include <utility>
using namespace std;

vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans;
    map<pair<int, int>, int> mpp;
    for (int row = 0; row < numRows; row++) {
        vector<int> temp;
        for (int col = 0; col <= row; col++) {
            if (col == 0 || col == row) {
                temp.push_back(1);
                mpp[make_pair(row, col)] = 1;
            } else {
                mpp[make_pair(row, col)] = mpp[make_pair(row - 1, col - 1)] + mpp[make_pair(row - 1, col)];
                temp.push_back(mpp[make_pair(row, col)]);
            }
        }
        ans.push_back(temp);
    }
    return ans;
}
