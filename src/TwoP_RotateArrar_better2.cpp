//轮转数组
/*
先反转数组 再分别反转从k为分界点的两个数组
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void rotate(vector<int>& nums, int k){
    int n = nums.size();
    k = k % n;
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin()+k);
    reverse(nums.begin()+k, nums.end());
}

int main(){

    vector<int> nums = {1,2,3,4,5,6,7};
    for(int i : nums){
        cout << i << ' ';
    }
    cout << endl;
    rotate(nums, 3);
    for(int i : nums){
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}