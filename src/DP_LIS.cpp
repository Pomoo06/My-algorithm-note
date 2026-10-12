//最长上升子序列
/*
在给定的数列里找到最长的不要求连续的上升子序列 
递推关系
dp[i] = max(dp[j] + 1) nums[j] < nums[i]
dp[i] 表示以nums[i]结尾的最长上升子序列长度
*/

#include <iostream>
#include <vector>

using namespace std;

int LIS(vector<int> &nums){
    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return 1;

    vector<int> dp(n, 1);
    int ans = 1;

    //遍历整个nums数组
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(nums[j] < nums[i]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }

    return ans;
}

int main(){
    vector<int> nums = {10,9,2,5,3,7,101,18};
    cout << LIS(nums) << endl;
    return 0;
}