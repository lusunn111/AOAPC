#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

//N<=10
int N;
int row[10];
int column[10];
int dp[10][10];
int split_ind[10][10];
int cases=0;

void print(int l, int r){
    if(l>r){
        return;
    }else if(l==r){
        cout << 'A' << l+1; //一旦l==r就可以打印数字了，因为这是最小单元了
    }else{
        cout << '('; //一旦l小于r就打印左括号，因为l<r说明l-r之间一定有一个k处有右括号，打印左括号与它匹配
        print(l, split_ind[l][r]);
        cout << " x ";
        print(split_ind[l][r]+1, r);
        cout << ')';
    }
}

int main() {
    while(cin>>N && N!=0){
        ++cases;
        for(int i=0; i<10; ++i){
            for(int j=0; j<10; ++j){
                dp[i][j] = INT_MAX;
            }
        }
        memset(split_ind, 0, sizeof(split_ind));

        for(int i=0; i<N; ++i){
            cin >> row[i] >> column[i];
        }
        //迭代法，j-i的方向递增，因为长区间依赖短区间
        for(int delta=0; delta<N; ++delta){
            for(int i=0; i+delta<N; ++i){
                if(delta==0){
                    dp[i][i+delta] = 0;
                }else if(delta==1){
                    dp[i][i+delta] = row[i]*column[i]*column[i+delta];
                    split_ind[i][i+delta] = i;
                }else{
                    for(int k=i; k<i+delta; ++k){
                        int temp_cal = dp[i][k] + dp[k+1][i+delta] + row[i]*column[k]*column[i+delta];
                        if(temp_cal<dp[i][i+delta]){
                            dp[i][i+delta] = temp_cal;
                            split_ind[i][i+delta] = k;
                        }
                    }
                }
            }
        }

        cout << "Case " << cases << ": ";
        print(0, N-1);
        cout << endl;
    }
}
