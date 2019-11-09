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

//递归法
int search(int l, int r){
    if(dp[l][r]!=INT_MAX) return dp[l][r];
    for(int k=l; k<r; ++k){
        if(search(l, k)+ search(k+1, r) + row[l]*column[k]*column[r] < dp[l][r]){
            dp[l][r] = search(l, k)+ search(k+1, r) + row[l]*column[k]*column[r];
            split_ind[l][r]=k;
        }
    }
    return dp[l][r];
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

        search(0, N-1);
        cout << "Case " << cases << ": ";
        print(0, N-1);
        cout << endl;
    }
}
