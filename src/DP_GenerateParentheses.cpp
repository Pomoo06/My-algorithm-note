//所有合法的括号组合
#include <vector>
#include <string>
#include <iostream>
using namespace std;


    vector<string> generateParenthesis(int n) {
        if(n == 1) return {"()"};

        vector<vector<string>> dp(n+1);

        dp[0] = {""};
        //每个括号都可以拼接成(A)B形式
        //有几对括号
        for(int i = 1; i <= n; i++){
            //确定()里有多少()
            for(int j = 0; j < i; j++){
                //()里有j个() 外有 i-j-1个 
                for(auto in : dp[j]){
                    for(auto out : dp[i-1-j]){
                        dp[i].push_back("(" + in + ")" + out);
                    }
                }
            }
        }

        return dp.back();

    }


int main(){

    auto res = generateParenthesis(5);
    for(auto i : res){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}