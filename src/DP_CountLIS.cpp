//最长上升子序列的个数

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();
    if(n == 1) return 1;

    vector<int> dp(n, 1);   //dp[i]表示以nums[i]结尾的最长上升子序列长度
    vector<int> cnt(n, 1);  //cnt[i]表示以nums[i]结尾的最长上升子序列个数



    for(int i = 0; i < n; i++){

        for(int j = 0; j < i; j++){

            if(nums[i] > nums[j]){

                if(dp[j] + 1 > dp[i]){
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if(dp[j] + 1 == dp[i]){
                    cnt[i] += cnt[j];
                }
            }
        }   

    }

    int res = 0;
    int max_len = *max_element(dp.begin(), dp.end());

    for(int i = 0; i < n; i++){
        if(dp[i] == max_len){
            res += cnt[i];
        }
    }

    return res;

}

int main(){


    vector<int> nums = {1, 2, 5, 4, 7};
    cout << findNumberOfLIS(nums) << endl;
    return 0;
}