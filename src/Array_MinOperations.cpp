//排序排列的最小操作数
/*
给出一个长度为n数组 数组的元素是0到n-1的排列
通过左移数组或反转数组 使得数组升序 求最小操作数
*/

#include<iostream>
#include<vector>

using namespace std;

int MinOperations(vector<int>& nums){
    int n = nums.size();
        if(n == 0) return 0;

        bool begin = false;
        vector<int> temp(2*n);

        for(int i = 0; i < n; i++){
            temp[i] = nums[i];
            temp[i+n] = nums[i];
        }
        int count = 0;
        //升序
        for(int i = 0; i < 2*n; i++){
            if(temp[i] == 0){
                count = i;
                begin = true;
            }

            if(i - count == n-1)
                return count;
            
            if(begin){
                if(temp[i] > temp[i+1]){
                    begin = false;
                    break;
                }
            }
            

        }
        //降序
        for(int i = 0; i < 2*n; i++){
            if(temp[i] == n-1){
                count = i;
                begin = true;
            }

            if(i - count == n-1)
                return count + 1;

            if(begin){
                if(temp[i] < temp[i+1]){
                    break;
                }
            }
            
        }

        return -1;
        

}

int main(){
    vector<int> nums1 = {0, 2, 1};
    cout << MinOperations(nums1) << endl;
    
    vector<int> nums2 = {2, 0, 1, 3};
    cout << MinOperations(nums2) << endl;
    
    return 0;
}