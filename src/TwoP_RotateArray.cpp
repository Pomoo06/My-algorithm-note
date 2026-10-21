//轮转数组
/*
给出一个数组和k 要求将每个元素向后移动k个位置
*/

#include<iostream>
#include<vector>

using namespace std;

void rotate(vector<int>& nums, int k){
    int n = nums.size();
    k = k % n;
    int p = k;
    vector<int> res(n,0);
    
    for(int i = 0; i < n; i++){
        res[p] = nums[i];
        p = (p+1) % n;
    }
    nums = res;
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