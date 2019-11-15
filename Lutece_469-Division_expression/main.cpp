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

int X[100005];
string str;
int cnt;
//分母最少的情况是只有X2,且X2一定在分母上，所以只需要看（X1×X3×...)/X2是不是整数

//法一：将每个数进行素因子分解。Xi<=2000000000，要求出多少个素因子？有点麻烦。

//法二：依次除以最大公约数，直到X2除到1为止
int gcd(int a, int b){
    if(b==0) return a;
    else{
        return gcd(b, a%b);
    }
}

bool divide(){
    for(int i=1; i<=cnt; ++i){
        if(i==2) continue;
        int g = gcd(X[i], X[2]);
        X[2] /= g;
        if(X[2]==1) break;
    }
    return X[2] == 1;
}

void readX(){
    size_t len = str.length();
    string::size_type pos1, pos2;
    pos2 = str.find('/');
    pos1 = 0;
    while(pos2!=string::npos){
        X[cnt++] = std::stoi(str.substr(pos1, pos2));
        pos1 = pos2+1;
        pos2 = str.find('/', pos1);
    }
    if(pos1!=string::npos){
        X[cnt] = std::stoi(str.substr(pos1));
    }
}

int main() {
    while(getline(cin, str)){
        cnt = 1;
        readX();
        if(divide()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}

