//冒泡排序
/*
将最值放到一边 每次比较相邻的两个数 如果前面的数大于后面的数 则交换位置
时间复杂度  O(n^2)
空间复杂度  O(1)
*/
#include<iostream>
#include<vector>

using namespace std;

static int swap_cnt = 0;
static int cmp_cnt = 0;
void BubbleSort(vector<int>& nums){
    int n = nums.size();

    bool change;

    for(int i = 0; i < n-1; i++){
        change = false;

        for(int j = 0; j < n-i-1; j++){
            cmp_cnt++;
            if(nums[j] > nums[j+1]){
                swap_cnt++;
                swap(nums[j], nums[j+1]);
                change = true;
            }
        }
        if(!change) break;
        
    }
}

int main(){

    vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    BubbleSort(nums);
    cout << "swap_cnt: " << swap_cnt << endl;
    cout << "cmp_cnt: " << cmp_cnt << endl;
    cmp_cnt = 0;
    swap_cnt = 0;
    vector<int> nums1 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    BubbleSort(nums1);
    cout << "swap_cnt: " << swap_cnt << endl;
    cout << "cmp_cnt: " << cmp_cnt << endl;


    return 0;

}