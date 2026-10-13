//解码方法
/*
在由数字构成的字符串中 给出所有可能的合法编码数
1 -> A
26 -> Z
06 -> 非法
*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;

int numDecodings(string s){
    int n = s.size();
    if(n == 0 || s[0] == 0) return 0;

    vector<int> dp(n+1, 0);
    dp[0] = 1;      //空字符串有一种编码 返回0
    dp[1] = 1;      //非0开头的字符串有一种编码 

    for(int i = 2; i <= n; i++){
        //当前字符不为0可独立编码
        if(s[i-1] != '0'){
            dp[i] += dp[i-1];       //到第i位时 对于独立编码合法编码数不变
        }

        int two_dig = (s[i-2] - '0') * 10 + (s[i-1] - '0');
        if(two_dig >= 10 && two_dig <= 26){
            dp[i] += dp[i-2];       //到第i位时 能组合编码的合法编码数等于与前一位合法编码数的和
        }
    }

    return dp[n];
}

int main(){
    string s = "1827423920";
    cout << numDecodings(s) << endl;
}