//选择排序
/*
每次选择最大或最小放到当前遍历位置
时间复杂度  O(n^2)
空间复杂度  O(1)
不稳定
*/

#include<iostream>
#include<vector>

using namespace std;

void selectSort(vector<int>& nums){

    int n = nums.size();
    for(int i = 0; i < n-1; i++){
        int min = i;
        for(int j = i+1; j < n; j++){
            if(nums[j] < nums[min]){
                min = j;
            }
        }
        swap(nums[i], nums[min]);
    }
}

int main(){

    vector<int> nums = {5, 4, 3, 2, 1};
    selectSort(nums);
    for(auto& num : nums){
        cout << num << " ";
    }
    cout << endl;
    return 0;
}