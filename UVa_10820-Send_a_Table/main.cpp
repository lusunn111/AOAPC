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

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

int n, m;
map<int, int> fac_m;
map<int, int> fac_Cni;

//本质就是求有多少个2元组（x，y）满足：1 <= x,y <= n，且x与y互素。
//除了（1，1）之外，其他所有的x和y都不相同，我们设x<y的二元组有f(n)个，答案就是2f(n)+1 f(n)=phi(2)+phi(3)+...+phi(n);
//phi(n)=n(1-1/p1)(1-1/p2)...(1-1/pk) pk为n的素因子

/*
//求1～n且与n互素的数
int phi(int n){
    int ans = n;
    for(int i=2; i<n; ++i){
        if(n%2==0){
            ans = ans/i*(i-1);
            while(n%2==0){
                n/=2;
            }
        }
    }
    if(n>1) ans = ans/n*(n-1);
    return ans;
}
*/

int phi[50005];

int main() {
    int N;
    while(cin>>N && N!=0){
        memset(phi, 0, sizeof(phi));
        phi[1] = 1;
        for(int i=2; i<=N; ++i){//2～N要么是素数，要么是素数的倍数，全能处理全
            if(!phi[i]){
                for(int j=i; j<=N; j+=i){//素数的倍数的情况全在这边处理
                    if(!phi[j]) phi[j]=j;
                    phi[j] = phi[j]/i*(i-1);
                }
            }
        }

        int res(0);
        for(int i=2; i<=N; ++i){
            res += phi[i];
        }
        cout << 2*res+1 << endl;
    }
}
