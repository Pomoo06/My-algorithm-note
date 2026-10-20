//快速排序
/*
通过基准元素划分两部分递归排序
每次递归能保证比基准元素小的元素都在左侧 比基准元素大的都在右侧
分区足够小时 数组就能保证有序-
时间复杂度  O(nlogn)
空间复杂度  O(logn)
*/

#include<iostream>
#include<vector>

using namespace std;

int partition(vector<int>& nums, int l, int r){
    int piovt = nums[r];

    int i = l - 1;
    for(int j = l; j < r; j++){
        if(nums[j] <= piovt){
            i++;
            swap(nums[i], nums[j]);
        }
    }

    swap(nums[i+1], nums[r]);

    return i+1;

}

void quickSortImpl(vector<int>& nums, int l, int r){
    if(l >= r) return;

    int p = partition(nums, l, r);

    quickSortImpl(nums, l, p-1);
    quickSortImpl(nums, p+1, r);
}

void quickSort(vector<int>& nums){
    int n = nums.size();
    if(n <= 1) return;
    int l = 0;
    int r = nums.size() - 1;

    quickSortImpl(nums, l, r);
}

int main(){
    vector<int> nums = {3, 5, 1, 9, -3,0, 7};
    quickSort(nums);

    for(int i : nums){
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}