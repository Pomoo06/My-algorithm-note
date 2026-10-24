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
        mp[i] += i;         //哈希表默认值0 直接累加即可
    }

    vector<pair<int, int>> vec(mp.begin(), mp.end());   //通过将哈希表转化为动态数组 便于后期排序
    sort(vec.begin(), vec.end());   //排序 通过key进行排序 保证动态数组的key是升序 方便进行取舍

    int take = 0;           //拿取当前得分 
    int skip = 0;           //跳过当前得分 拿取前一得分
    int per_key = 0;        //记录前一个key 方便进行取舍

    for(auto& [key, val] : vec){

        int cur_take = val + (key == per_key +1 ? skip : max(skip, take));
        /*
        int cur_take = take + (key == per_key +1 ? skip : max(skip, take));
        对于此句 cur_take指的是拿取当前的得分 如果前驱存在 就只能拿取跳过前驱的得分 
        即 当 key == per_key + 1 时 cur_take = val + skip
        否则 前驱不存在 此时拿取skip和take都不会影响现在的取舍 就取take和skip的最大值 
        即 当 key != per_key + 1 时 cur_take = val + max(skip, take)
        */
        int cur_skip = max(skip, take);
        /*
        int cur_skip = max(skip, take);
        对于此句 cur_skip指的是跳过当前得分 就不会触发删除相邻数字的乘法
        那么skip就应该取拿取这个前一个数的得分或者跳过前一个数得分的最大值
        即 当前得分和前一得分的最大值 即 max(skip, take)
        */

        take = cur_take;    //更新当前得分
        skip = cur_skip;    //更新跳过当前得分
        per_key = key;      //更新前驱
    }

    return max(take, skip);     //返回得分的最大值

}

int main(){
    vector<int> nums = {2,2,3,3,3,4};
    cout << MaxScore(nums) << endl;

    return 0;
}