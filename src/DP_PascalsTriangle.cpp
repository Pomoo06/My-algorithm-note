//构造杨辉三角

#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> triangle(int nums){
    int n = nums;
        if(n == 1) return{{1}};

        vector<vector<int>> dp(n, vector<int>{1});

        for(int i = 1; i < n; i++){
            for(int j = 1; j < i; j++){
                dp[i].push_back(dp[i-1][j-1] + dp[i-1][j]);
            }
            dp[i].push_back(1);
        }

        return dp;
}

int main(){

    vector<vector<int>> res = triangle(6);
    for(auto i : res){
        for(auto j : i){
            cout << j << ' ';
        }
        cout << endl;
    }
    return 0;
}