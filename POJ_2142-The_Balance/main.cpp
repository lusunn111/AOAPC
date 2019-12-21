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

typedef long long ll;

int exgcd(int a, int b, int&x, int& y){
    if(b==0){
        x = 1;
        y = 0;
        return a;
    }else{
        int p = exgcd(b, a%b, x, y);
        int temp = x;
        x = y;
        y = temp - a/b*y;
        return p;
    }
}

int main() {
    int a, b, d;
    while(cin>>a>>b>>d && (a || b || d)){
        int x, y;
        int g = exgcd(a, b, x, y); //x满足ax+by=gcd(a,b)=g

        int x1 = x, x2 = x, y1 = y, y2 = y;
        x1 *= d/g; //x满足ax+by=d，下一步要求最小的正x，就是逆元
        int t = b/g;//满足(a/g)x+ty = 1的最小x就是满足ax+by=g的最小x
        x1 = (x1%t+t)%t;
        y1 = std::abs((d-a*x1)/b);

        y2 *= d/g;
        t = a/g;
        y2 = (y2%t+t)%t;
        x2 = std::abs((d-b*y2)/a);

        if(x1+y1 < x2+y2){
            cout<<x1<<" "<<y1<<endl;
        }else{
            cout<<x2<<" "<<y2<<endl;
        }
    }
}
