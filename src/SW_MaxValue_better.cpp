//求滑动窗口的最大值
/*
和前一个解法相比 当数列是递减数列时 每次滑动窗口都会进行比较 时间复杂度会退化成O(nk)
使用单调双头队列时 可以将时间复杂度稳定在O(n)
*/

#include<iostream>
#include<vector>
#include<deque>

using namespace std;

vector<int> maxValue(vector<int>& nums, int k){
    deque<int> dq;
    vector<int> res;

    int n = nums.size();
    for(int i = 0; i < n; i++){
        //队不空且队头元素在滑动窗口外 弹出队头元素
        if(!dq.empty() && dq.front() <= i-k) dq.pop_front();
        //把小于当前元素的元素从队尾弹出
        while(!dq.empty() && nums[dq.back()] <= nums[i]){
            dq.pop_back();
        }
        //无条件插入当前元素
        dq.push_back(i);
        //窗口成立放进res
        if(i >= k-1) res.push_back(nums[dq.front()]);
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