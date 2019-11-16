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

//求num的约数个数
/*
1.约数个数定理：对于一个数a可以分解质因数：a＝a1的r1次方乘以a2的r2次方乘以a3的r3次方乘以……

则a的约数的个数就是（r1＋1）（r2＋1）（r3＋1）……

需要指出来的是，a1，a2，a3……都是a的质因数。r1，r2，r3……是a1，a2，a3……的指数。

2.判断m的约数个数:将m开方得n，判断n之前属于m的约数个数num。若n为整数，则m约数个数为2*num+1，否则为2*num，加速
*/
int divisors(int num){
    int res = 1;
    for(int i=2; i*i<=num; ++i){
        int cnt(1);
        while(num%i==0){
            ++cnt;
            num/=i;
        }
        res *= cnt;
        if(num==1) break;
    }
    if(num>1) res *= 2;
    return res;
}

int main() {
    int N;
    cin >> N;
    while(N--){
        int L, U;
        cin >> L >> U;
        int max(0);
        int max_ind(0);
        for(int i=L; i<=U; ++i){
            int temp = divisors(i);
            if(temp>max){
                max=temp;
                max_ind=i;
            }
        }

        cout << "Between " << L << " and " << U << ", " << max_ind << " has a maximum of " << max << " divisors." << endl;
    }
}
