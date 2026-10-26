//总价值可被k整除的岛屿数
/*
和Island相似 通过淹没岛屿获得价值求价值总和 
*/

#include<vector>
#include<iostream>

using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(vector<vector<int>>& grid, int i, int j, long long int& sum){
    if(i >= grid.size() || j >= grid[0].size() || i < 0 || j < 0 || grid[i][j] == 0)
        return;

    sum += grid[i][j];
    grid[i][j] = 0;

    for(int d = 0; d < 4; d++){
        dfs(grid, i+dx[d], j+dy[d], sum);
    }
}

int IslandValue(vector<vector<int>>& grid, int k){
    int m = grid.size();
    int n = grid[0].size();

    int res = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] > 0){
                long long int sum = 0;
                dfs(grid, i, j, sum);
                if(sum % k == 0)
                    res++;
            }
        }
    }

    return res;
}

int main(){


    vector<vector<int>> grid = {{0,2,1,0,0},{0,5,0,0,5},{0,0,1,0,0},{0,1,4,7,0},{0,2,0,0,8}};
    cout << IslandValue(grid, 2);
    return 0;
}