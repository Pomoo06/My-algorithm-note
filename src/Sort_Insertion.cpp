//插入排序
/*
将数列分类成已排序和未排序两部分，
从未排序部分取出一个元素，插入到已排序部分的适当位置，
重复上述过程，直到未排序部分为空。
时间复杂度  O(n^2)
空间复杂度  O(1)
稳定
*/

#include<iostream>
#include<vector>

using namespace std;

void InsertionSort(vector<int>& nums){
    int n = nums.size();
    for(int i = 1; i < n; i++){
        
      int temp = nums[i];
      int j = i-1;
      while(j >= 0 && nums[j] > temp){
        nums[j+1] = nums[j];
        j--;
      }
      nums[j+1] = temp;
    
    }
}

int main(){

    vector<int> nums = {5, 4, 3, 2, 1};
    InsertionSort(nums);
    for(auto& num : nums){
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
