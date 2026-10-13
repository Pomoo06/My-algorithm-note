//返回杨辉三角第i行
#include<iostream>
#include<vector>

using namespace std;

vector<int> getRow(int rowIndex) {
        int n = rowIndex + 1;
        if(n == 1) return{1};

        vector<vector<int>> dp(n, vector<int>{1});

        for(int i = 1; i < n; i++){
            for(int j = 1; j < i; j++){
                dp[i].push_back(dp[i-1][j-1] + dp[i-1][j]);
            }
            dp[i].push_back(1);
        }

        return dp[n-1];
    }

int main(){

    vector<int> res = getRow(30);
    for(auto i : res){
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}