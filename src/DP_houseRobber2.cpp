//打家劫舍
//在环形街上不连续的房子里偷东西 求偷盗的最大金额

#include <iostream>
#include <vector>
using namespace std;

int son(vector<int> &nums, int start, int end){
    if(start == end) return nums[start];        //当只有两个房子时 进入子函数start和end都为1 所以需要单独处理

    vector<int> dp(end-start+1);
    dp[0] = nums[start];
    dp[1] = max(nums[start], nums[start+1]);

    for(int i = start+2; i <= end; i++){
        dp[i-start] = max(dp[i-start-1], dp[i-start-2] + nums[i]);  //i是全局索引 start是偏移量 i-start是修正后dp数组的索引
    }

    return dp.back();
}

int rob(vector<int>& nums){
    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return nums[0];

    int res1 = son(nums, 0, n-2); //偷第一个房子
    int res2 = son(nums, 1, n-1); //不偷第一个房子

    return max(res1, res2);
}

int main(){
    vector<int> nums = {2,7,9,3,1};
    cout << rob(nums) << endl;
    return 0;
}