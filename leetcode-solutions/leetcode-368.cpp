#include <vector>
#include <algorithm>
using namespace std;

vector<int> largestDivisibleSubset(vector<int>& nums) {
        if(nums.size()==0 || nums.size()==1)
            return nums;
    
        sort(nums.begin(),nums.end());
        vector<int> dp(nums.size(),1);
        for(int i=1;i<nums.size();i++){
            for(int j=0;j<i;j++){
                if(nums[i]%nums[j]==0){
                    dp[i]=max(dp[i],1+dp[j]);
                }                    
            }                
        }
        
        int maxi=*max_element(dp.begin(),dp.end());
        
        int prev=-1;
        int i=dp.size()-1;
        vector<int> res;
        while(i>=0) {
            if(dp[i]==maxi && (prev%nums[i]==0 || prev==-1) ) {
                res.push_back(nums[i]);
                maxi--;
                prev=nums[i];
            }
            i--;
        }
        return res;
    }