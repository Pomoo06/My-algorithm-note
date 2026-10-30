//01背包问题
/*
你有一个容量为 w 的背包，和 n 件物品。
第 i 件物品的重量是 weight[i]，价值是 value[i]。
每件物品只有一个（不能重复选）。
目标：在背包容量不超载的前提下，让背包里的物品总价值最大。
*/

#include<iostream>
#include<vector>

using namespace std;

int Bag(int w, vector<int>& weight, vector<int>& value){

    int n = weight.size();

    vector<vector<int>> dp(n, vector<int>(w+1, 0));

    for(int i = 0; i < n; i++)
}

int main(){

    int n = 3;
    int w = 4;
    vector<int> weight = {2,1,3};
    vector<int> value = {4,2,3};
    cout << Bag(w, weight, value);

    return 0;
}