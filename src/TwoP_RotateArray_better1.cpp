//轮转数组
/*
前一个解法需要的空间是O(n) 用原地算法实现 空间复杂度O(1)
*/

#include<iostream>
#include<vector>
#include<numeric>

using namespace std;

void rotate(vector<int>& nums, int k){
    int n = nums.size();
    
    if(n == 1) return;
    if(n < k) k = k % n;
    if(k == 0) return;

    int g = gcd(n, k);
    for(int start = 0; start < g; start++){
        int cur = start;
        int temp = nums[cur];
        do{
            int nxt = (cur+k) % n;
            int t = nums[nxt];
            nums[nxt] = temp;
            temp = t;
            cur = nxt; 
        }
        while(cur != start);

    }

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