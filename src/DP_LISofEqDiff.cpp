//最长等差子序列
/*
对于给定的数组arr和差值diff，返回arr的最长等差子序列长度。
*/
/*
和LIS的区别是 LIS只有nums[i] > nums[j]这一个约束 不够严谨 没法推导前一个元素是什么
LISofEqDiff 有两个约束 1. nums[i] - nums[j] == diff  可以保证每一个元素都能找到他的前驱 不存在直接记0
*/

#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

int LISofEqDiff(vector<int>& arr, int diff){
    int n = arr.size();
    if(n == 1) return 1;
    unordered_map<int, int> dp;
    
    int res = 0;
    for(int i : arr){
        dp[i] = max(dp[i-diff], dp[i-diff-diff]) + 1;
        res = max(res, dp[i]);
    }

    return res;
}

int main(){

    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int diff = 2;
    cout << LISofEqDiff(arr, diff) << endl;
    return 0;
}

