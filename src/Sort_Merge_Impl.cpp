//归并排序 递归

#include<iostream>
#include<vector>

using namespace std;

void merge(vector<int>& nums, vector<int>& tmp, int l, int mid, int r){
  int i = l;
  int j = mid + 1;
  int k = l;

  while(i <= mid && j <= r){
    if(nums[i] <= nums[j])
      tmp[k++] = nums[i++];
    else
      tmp[k++] = nums[j++];
  }

  while(i <= mid){
    tmp[k++] = nums[i++];
  }

  while(j <= r){
    tmp[k++] = nums[j++];
  }

  for(int p = l; p <= r; ++p)
    nums[p] = tmp[p];

}

void mergeSortImpl(vector<int>& nums, vector<int>& tmp, int l, int r){
  if(l >= r) return;

  int mid = l + (r-l) / 2;

  mergeSortImpl(nums, tmp, l, mid);
  mergeSortImpl(nums, tmp, mid+1, r);

  merge(nums, tmp, l, mid, r);
}

void mergeSort(vector<int>& nums){
  int n = nums.size();
  if(n <= 1) return;

  vector<int> tmp(n);
  mergeSortImpl(nums, tmp, 0, n-1);

}

int main(){

  vector<int> nums = {1,6,3,9,3,0,-4,-6,35,9};
  
  mergeSort(nums);

  for(int i : nums)
    cout << i << ' ';
  cout << endl;
  return 0;
}