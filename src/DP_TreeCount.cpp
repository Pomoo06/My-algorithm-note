//搜索二叉树数量
/*
对于给定的正整数n，计算有多少个搜索二叉树可以存储n个元素
搜索二叉树的定义：
1. 每个节点都有一个唯一的整数值
2. 每个节点的左子树的值都小于当前节点的值
3. 每个节点的右子树的值都大于当前节点的值

根只分为左子树和右子树 左子树和右子树的形状相互独立
当有根节点为i时 将左右子树分为k-1个和i-k个节点
此时有dp[k-1] * dp[i-k]种形状
遍历k相加求和得到dp[i]
*/

#include<iostream>
#include<vector>

using namespace std;

long long int TreeCount(int n){
    vector<long long int> dp(n+1);

    dp[0] = 1;

    for(int i = 1; i <= n; i++){
        for(int k = 1; k <= i; k++){
            dp[i] += dp[k-1] * dp[i-k];
        }
    }

    return dp[n];
}

int main(){

    cout << TreeCount(10);

    
    return 0;
}