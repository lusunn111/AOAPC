#include <iostream>
#include <cstring>
#include <cfloat>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <map>
#include <numeric>
#include <climits>
#include <cstring>

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

typedef long long ll;
#define F(i, j) (f[(i)+1][(j)+1])

ll f[405][405]={0};

//f(n,k)=f(n-1,k)+f(n-2,k-n)
//n<=0, k>=0, f(n,k)=0
//n<=0, k<0, f(n,k)=1
int main(){
    int n, k;
    cin >> n >> k;
    for(int i=0; i<=k; ++i){
        F(-1, i) = 0; F(0, i) = 0;
    }
    F(-1, -1) = F(0, -1) = 1;
    for(int i=1; i<=n; ++i){
        for(int j=-1; j<=k; ++j){
            F(i, j) = F(i-1, j);
            if(j-i>=0){
                F(i, j) += F(i-2, j-i);//i=1,i=2时边界条件F(-1, i),F(0,i)
            }else{
                F(i, j) += F(i-2, -1);//i=1,i=2时边界条件F(-1, -1),F(0,-1)
            }
        }
    }
    cout << F(n, k) << endl;
}

