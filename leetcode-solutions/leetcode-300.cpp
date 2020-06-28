#include <vector>
#include <iterator>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
	vector<int> dp;
	for (const auto& num : nums) {
		auto up = lower_bound(nums.begin(), nums.end(), num);
		if (up != dp.end()) {
			*up = num;
		}
		else {
			dp.emplace_back(num);
		}
	}
	return dp.size();
}