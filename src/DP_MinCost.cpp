//最小爬楼梯代价

#include<iostream>
#include<vector>

using namespace std;

int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        if(n == 2) return min(cost[0], cost[1]);

        vector<int> dp(n);
        dp[0] = cost[0];
        dp[1] = min(cost[0], cost[1]);

        for(int i = 2; i < n; i++){
            dp[i] = min(dp[i-1], dp[i-2]) + cost[i];
        }

        return min(dp[n-1], dp[n-2]);
    }

int main(){

    vector<int> cost = {10, 15, 20};
    cout << minCostClimbingStairs(cost) << endl;

    return 0;
}