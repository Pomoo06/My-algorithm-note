//打家劫舍
//在不连续的房子里偷东西 求偷盗的最大金额
/*
在每个房子都有偷和不偷两种选择
dp[i] 表示偷到第i个房子时的最大金额
比较偷完这个房子和不偷这个房子时的最大金额
不偷这个房子时，dp[i] = dp[i-1]
偷这个房子时，dp[i] = dp[i-2] + nums[i]
dp[i] = max(dp[i-1], dp[i-2] + nums[i])
*/
#include <iostream>
#include <vector>
using namespace std;

int rob(vector<int>& nums){
    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return nums[0];

    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for(int i = 2; i < n; i++){
        dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
    }
    return dp.back();
}

int main(){
    vector<int> nums = {2,7,9,3,1};
    cout << rob(nums) << endl;
    return 0;
}