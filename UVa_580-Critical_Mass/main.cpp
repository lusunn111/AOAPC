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

int f[31]={0};
int g[31]={0};

//g(n)=2^n-f(n)，g(n)为1~n不包含连续3个U的解数
//f(n)是1～n包含至少一个3个U的解数
//f(n)=2^n-3+g(i-2)*2^(n-i-2),i=2~n-2
int main(){
    f[0]=f[1]=f[2]=0;
    g[0]=1;
    g[1]=2;
    g[2]=4;
    for(int n=3; n<31; ++n){
        f[n] = std::pow(2, n-3);
        for(int i=2; i<=n-2; ++i){
            f[n] += g[i-2]*std::pow(2, n-i-2);
        }
        g[n] = std::pow(2,n)-f[n];
    }
    int n;
    while(cin>>n&&n!=0){
        cout << f[n] << endl;
    }
}

