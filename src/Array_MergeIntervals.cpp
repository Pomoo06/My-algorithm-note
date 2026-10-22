//合并区间
/*
给出一个由区间构成的二维数组
合并所有重叠的区间
把所有区间按左端点排序 保证所有可合并区间连续 后比较两个区间端点值
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> merge(vector<vector<int>>& nums){
    int n = nums.size();
    if(n == 0) return {{}};
    sort(nums.begin(), nums.end());

    vector<vector<int>> res;

    for(auto& i : nums){
        if(res.empty() || res.back()[1] < i[0]){
            res.push_back(i);
        }
        else{
            res.back()[1] = max(res.back()[1], i[1]);
        }
    }

    return res;
    
}

int main(){

    vector<vector<int>> nums = {{1,3},{2,6},{8,10},{15,18}};
    for(auto i : nums){
        for(auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }
    vector<vector<int>> res = merge(nums);
    for(auto i : res){
        for(auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}