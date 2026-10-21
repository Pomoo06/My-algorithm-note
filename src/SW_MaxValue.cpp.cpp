//给出一个数组nums， 整数k， 在滑动窗口宽度为K时 把每个窗口的最大元素都记录下来
/*
如果前一个最大值在下一个窗口-> 直接比较新进入的值和最大值
如果前一个最大值不在下一个窗口->在新窗口寻找最大值 更新最大值的索引
*/

#include<iostream>
#include<vector>

using namespace std;

vector<int> maxValue(vector<int>& nums, int k){
    int n = nums.size();

    if(n == 1) return {nums[0]};

    int l = 0;
    int r = l + k - 1;
    int max_idx = -1;

    vector<int> res;

    while(r < n){
        
        if(max_idx < l){
            int max_val = nums[l];
            for(int i = l; i <= r; i++){
                if(nums[i] >= max_val){
                    max_val = nums[i];
                    max_idx = i;
                }
            }
            res.push_back(max_val);
        }
        else{
            if(nums[r] >= nums[max_idx]){
                res.push_back(nums[r]);
                max_idx = r;
            }
            else{
                res.push_back(nums[max_idx]);
            }
        }

        l++;
        r++;
    }

    return res;

}

int main(){

    vector<int> nums = {1,2, 5, 7, 3, 10, 30, 4, 29, 0, -9, -10, 4, 10};
    vector<int> res = maxValue(nums, 3);
    for(int i : res){
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}