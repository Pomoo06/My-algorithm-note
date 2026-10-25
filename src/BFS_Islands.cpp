//封闭岛屿数量
/*
二维矩阵 grid 由 0 （土地）和 1 （水）组成。岛是由最大的4个方向连通的 0 组成的群，封闭岛是一个 完全 由1包围（左、上、右、下）的岛。
请返回 封闭岛屿 的数目。
淹没法dfs 通过淹没边界和相连的岛屿 完成计数
*/

#include<iostream>
#include<vector>

using namespace std;

int dirs[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

void dfs(vector<vector<int>>& grid, int i, int j){
    //遇到水或者越界停止
    if(i <= 0 || i >= grid.size() || j <= 0 || j >= grid[0].size() || grid[i][j] == 1)
        return;
    //当前位置淹没
    grid[i][j] = 1;
    //递归淹没上下左右四个方向的陆地
    for(int d = 0; d < 4; d++){
        dfs(grid, i+dirs[0][d], j+dirs[1][d]);
    }
}

int numsIslands(vector<vector<int>>& grid ){

    int m = grid.size();
    int n = grid[0].size();
    //长宽小于3时 没有封闭岛屿
    if(n <= 2 || m <=2) return 0;
    //淹没边界上的陆地 防止后续的dfs 淹没边界上的陆地
    for(int i = 0; i < m; i++){
        dfs(grid, i, 0);
        dfs(grid, i, n-1);
    }
    for(int i = 0; i < n; i++){
        dfs(grid, 0, i);
        dfs(grid, m-1, i);
    }

    int res = 0;
    //剩余的陆地 就是封闭岛屿
    for(int i = 1; i < m-1; i++){
        for(int j = 1; j < n-1; j++){
            if(grid[i][j] == 0){
                res++;
                //淹没相邻岛屿
                dfs(grid, i, j);
            }
        }
    }

    return res;
}

int main(){

    vector<vector<int>> grid = {{0,0,1,0,0},{0,1,0,1,0},{0,1,1,1,0}};
    cout << numsIslands(grid) << endl;
    return 0;
}

