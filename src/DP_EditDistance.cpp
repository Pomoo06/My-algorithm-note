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

using namespace std;

