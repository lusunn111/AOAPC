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

//输入正整数n，m，输出n mod n的值。 n<=10^100，m<=10^9
// abcd % e = ((((a*10+b)*10+c)*10)+d) % e

vector<int> n(100, -1);
int m;

int main() {
    char c;
    int cnt=0;
    while((c=getchar()) != '\n'){
        n[cnt] = c-48;
        ++cnt;
    }
    cin >> m;

    int ans = 0;
    for(int i=0; i<cnt; ++i){
        ans = static_cast<int>(static_cast<ll>(ans*10+n[i])%m);
    }

    cout << ans << endl;
}
