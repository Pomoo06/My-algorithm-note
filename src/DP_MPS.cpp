//最大连续子序列乘积
/*
状态转移方程：
f(i) = max(f(i-1) * a[i], a[i])
连续负数时，需要记录最小值，以便后续计算最大值
*/

#include <iostream>
#include <vector>

using namespace std;

int MPS(vector<int> &nums){
    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return nums[0];

    vector<int> dp(n, 0);
    vector<int> dp2(n, 0);
    dp[0] = nums[0];
    dp2[0] = nums[0];
    int ans = nums[0];
    for(int i = 1; i < n; i++){
        dp[i] = max(dp[i-1]*nums[i], max(nums[i], dp2[i-1]*nums[i]));
        dp2[i] = min(dp2[i-1]*nums[i], min(nums[i], dp[i-1]*nums[i]));
        ans = max(ans, dp[i]);
    }

    return ans;
}

int main(){
    vector<int> nums = {2,3,-2,4,8,100,5,-10, -1000, -5};
    cout << MPS(nums) << endl;
    return 0;
}