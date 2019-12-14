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

// (a+b)%c = ((a%c)+(b%c))%c
// (a-b)%c = ((a%c)-(b%c)+c)%c
// (a*b)%c = ((a%c)(b%c))%c

//输入正整数a、n、m，输出a^n mod m的值，a，n，m<=10^9


vector<int> n(100, -1);
int m;

int main() {
    int a, n, m;
    cin >> a >> n >> m;
    int ans = 1;//ans一定在long long范围内
    for(int i=0; i<n; ++i){
        ans = static_cast<int>(static_cast<ll>(ans*a)%m); //ans*a可能大于int，但一定小于long long
    }
    cout << ans << endl;
}
