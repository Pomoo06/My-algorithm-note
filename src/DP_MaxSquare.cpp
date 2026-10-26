//最大正方形
/*
给出一个由字符1和0组成的矩阵 求这个矩阵里能构成的正方形的最大面积
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int MaxSquare(vector<vector<int>>& matrix){
    int m = matrix.size();
    int n = matrix[0].size();
    int res = 0;
    vector<vector<int>> dp(m, vector<int>(n,0));

    for(int i = 0; i < m; i++){
        if(matrix[i][0] == 1){
            res = 1;
            dp[i][0] = 1;
        }
    }
    for(int i = 0; i < n; i++){
        if(matrix[0][i] == 1){
            res = 1;
            dp[0][i] = 1;
        }
    }

    for(int i = 1; i < m; i++){
        for(int j = 0; j < n; j++){
            if(matrix[i][j] == 1){
                dp[i][j] = min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]}) + 1;
                res = max(res, dp[i][j]);
            }
        }
    }

    return res * res;
}

int main(){

    vector<vector<int>> matrix = {{1,0,1,0,0}, {1,0,1,1,1}, {1,1,1,1,1}, {1,0,0,1,0}};
    cout << MaxSquare(matrix) << endl;
    return 0;
}