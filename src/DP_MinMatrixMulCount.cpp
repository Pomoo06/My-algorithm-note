// 求最小矩阵数乘次数
#include <iostream>
#include <vector>

using namespace std;

int minMatrixMulCount(vector<int> &p, int n) {
    
    vector<vector<int>> m(n, vector<int>(n, 0));         //定义矩阵m[i][j]表示矩阵i到j的最小乘法次数
                                                                            
    for(int len = 1; len < n; len++){            //确定矩阵分割长度
        
        for(int i = 0; i < n - len; i++){       //确定矩阵分割的起始位置
            
            int j = i+ len;                     //通过j确定分割结束位置
            m[i][j] = INT_MAX;                 //初始化m[i][j]为无穷大

            for(int k = i; k < j; k++){         //确定分割点k
                
                int tmp = m[i][k] + m[k+1][j] + p[i] * p[k+1] * p[j+1];
                m[i][j] = min(m[i][j], tmp);

            }

        }
    }
    return m[0][n-1];
}

int main() {
    vector<int> p = {30, 35, 15, 6};
    cout << minMatrixMulCount(p, p.size()-1) << endl;
    return 0;
}