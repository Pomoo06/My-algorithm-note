//三角形最小路径和
/*
给出一个三角形 求自顶向下的最小路径和
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int triangle(vector<vector<int>> &triangle){
    int n = triangle.size();

    if(n == 1) return triangle[0][0];

    vector<vector<int>> dp(n, vector<int>(n));
    dp[0][0] = triangle[0][0];
    for(int i = 1; i < n; i++){
        dp[i][0] = triangle[i][0] + dp[i-1][0];
        dp[i][i] = triangle[i][i] + dp[i-1][i-1];
    }

    for(int i = 2; i < n; i++){
        for(int j = 1; j < i; j++){
            dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j];
        }
    }

    return *min_element(dp[n-1].begin(), dp[n-1].end());
}

int main(){
    vector<vector<int>> trgle{{1}, {2,3}, {4, 5, 6},{7, 8, 9, 10}};
    int res = triangle(trgle);
    cout << res << endl;
    return 0;
}