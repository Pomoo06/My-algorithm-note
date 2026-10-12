// 爬楼梯
#include<iostream>
#include<vector>

using namespace std;

int climbStairs(int n){
    vector<int> dp(n, 0);
    dp[0] = 1;
    dp[1] = 2;
    for(int i = 2; i < n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n-1];
}

int main(){
    int n = 5;
    cout << climbStairs(n) << endl;
    return 0;
}