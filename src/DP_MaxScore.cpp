//最大点数
/*
给出一个数组 每次拿取数组的元素作为得分时 都会删除数组中其他值与当前元素相差1的元素 求可获得的最大得分

通过哈希表 将数组中的元素作为key 数组中相同元素的和作为value 
通过对key进行排序 将原问题转化为打家劫舍问题 即拿取当前得分 或拿取当前得分前一个相差一的得分 
*/

#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

int MaxScore(vector<int>& nums){
    unordered_map<int, int> mp;
    for(int i : nums){
        mp[i] += i;
    }

    vector<pair<int, int>> vec(mp.begin(), mp.end());
    sort(vec.begin(), vec.end());

    int take = 0;
    int skip = 0;
    int per_key = 0;

    for(auto& [key, val] : vec){
        int cur_take = take + (key == per_key +1 ? skip : max(skip, take));
        int cur_skip = max(skip, take);

        take = cur_take;
        skip = cur_skip;
        per_key = key;
    }

    return max(take, skip);

}

int main(){
    vector<int> nums = {2,2,3,3,3,4};
    cout << MaxScore(nums) << endl;

    return 0;
}