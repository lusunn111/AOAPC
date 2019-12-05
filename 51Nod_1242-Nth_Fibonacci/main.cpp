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
const ll module = 1000000009;

/* TLE
int main() {
    ll n;
    cin >> n;
    int fib[4];
    fib[1] = 1;
    fib[2] = 1;
    for(int i=3; i<=n; ++i){
        fib[3] = (fib[1]%module+fib[2]%module)%module;
        fib[2] = fib[1];
        fib[1] = fib[3];
    }
    cout << fib[3] << endl;
}
 */

struct Node{
    ll d[2][2]; //不能是int，乘法过程可能溢出
};

Node mul(Node n1, Node n2){
    Node res;
    std::memset(res.d, 0, sizeof(res.d));
    for(int i=0; i<2; ++i){
        for(int j=0; j<2; ++j){
            for(int k=0; k<2; ++k){
                res.d[i][j] = (res.d[i][j] + n1.d[i][k]*n2.d[k][j])%module;
            }
        }
    }

    return res;
}

Node pow(Node a, ll n){
    Node ans = {1, 0, 0, 1};
    while(n){
        if(n & 1){
            ans = mul(ans, a);
        }
        a = mul(a, a);
        n >>= 1;
    }

    return ans;
}

//矩阵求斐波那契数列
int main(){
    ll n;
    cin >> n;
    Node init;
    init.d[0][0] = init.d[0][1] = init.d[1][0] = 1;
    init.d[1][1] = 0;

    Node res = pow(init, n);
    cout << res.d[1][0]%module << endl;
}
