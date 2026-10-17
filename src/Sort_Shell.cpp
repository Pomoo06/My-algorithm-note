//希尔排序
/*
通过控制增量来实现分组，然后对每组进行插入排序
时间复杂度：O(n^1.3)
空间复杂度：O(1)
*/

#include<iostream>
#include<vector>

using namespace std;

void Shell_Sort(vector<int>& nums){
    int n = nums.size();
    for(int gap = n/2; gap > 0; gap /= 2){
        for(int i = gap; i < n; i++){
            int temp = nums[i];
            int j = i - gap;
            while(j >= 0 && nums[j] > temp){
                nums[j+gap] = nums[j];
                j -= gap;
            }
            nums[j+gap] = temp;
        }

    }
}

int main(){

    vector<int> nums = {5, 4, 3, 2, 1, 0, -1, -2, -3, -4};
    Shell_Sort(nums);
    for(auto& num : nums){
        cout << num << " ";
    }
    cout << endl;
    return 0;
}