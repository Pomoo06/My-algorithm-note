//编辑距离
/*
给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数
你可以对一个单词进行如下三种操作：
插入一个字符
删除一个字符
替换一个字符
递推关系式
if word1[i-1] == word2[j-1]
    dp[i][j] = dp[i-1][j-1]
else
    dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1
*/


#include<iostream>   
#include<vector>     
#include<algorithm>  
#include<string>

using namespace std;

int editdistance(string word1, string word2){
    int m = word1.length();
    int n = word2.length();

    vector<vector<int>> dp(m+1, vector<int>(n+1));

    for(int i = 0; i <= m; i++){
        dp[i][0] = i;
    }

    for(int i = 0; i <= n; i++){
        dp[0][i] = i;
    }

    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(word1[i-1] == word2[j-1]){
                dp[i][j] = dp[i-1][j-1];
            }
            else{
                dp[i][j] = min({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]}) + 1;
            }
        }
    }

    return dp[m][n];


}

int main(){
    string word1 = "horse";
    string word2 = "ros";
    cout << editdistance(word1, word2) << endl;
    return 0;
}

