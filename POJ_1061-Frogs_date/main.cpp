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

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

typedef long long ll;

//(x+m*t)%L=(y+n*t)%L
//(m-n)*t%L=y-x
//即(m-n)*t1+L*t2=y-x有解
//扩展欧几里得算法可知有解的条件是(y-x)%gcd(m-n, L)=0

ll exgcd(ll a, ll b, ll& x, ll& y){
    if(b==0){
        x = 1;
        y = 0;
        return a;
    }else{
        ll p = exgcd(b, a%b, x, y);
        ll temp = x;
        x = y;
        y = temp - a/b*y;
        return p;
    }
}

int main() {
    ll x, y, m, n, L;
    cin >> x >> y >> m >> n >> L;
    ll a = m-n;
    ll b = L;
    ll t1, t2;
    ll d = exgcd(a, L, t1, t2);//求出的t1是(m-n)*t1+L*t2=gcd(m-n,L)的解
    if((y-x)%d){
        cout << "Impossible" << endl;
    }else{
        t1 *= (y-x)/d;
        t1 %= L;
        if(t1<0){
            t1 += L;
        }
        cout << t1 << endl;
    }
}
