//反转数字
/*
给你一个 32 位的有符号整数 x ，返回 x 中每位上的数字反转后的结果。
且不存在64位类型
如果反转后整数超过 32 位的有符号整数的范围 [−2^31, 2^31 − 1] ，就返回 0。

*/

#include<iostream>

using namespace std;


int reverse(int x) {
 
    int res = 0;
    while(x != 0){
        int pop = x % 10;
        x /= 10;

        if(res > INT_MAX /10 || (res == INT_MAX / 10 && pop > 7))
            return 0;
        if(res < INT_MIN / 10 || (res == INT_MIN / 10 && pop < -8))
            return 0;

        res = res * 10 + pop;
    }

    return res;
}

int main(){
    int x = -2147483412;
    cout << reverse(x) << endl;
    return 0;
}