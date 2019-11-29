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

int f[11]={0};

//f(n) = f(0)f(n-1)+f(1)f(n-2)+...+f(n-1)f(0)
int main(){
    f[0] = 1;
    f[1] = 1;
    for(int n=2; n<=10; ++n){
        for(int j=0; j<n; ++j){
            f[n] += f[j]*f[n-1-j];
        }
    }

    int n;
    int t=0;
    while(cin >> n){
        if(t++) cout << "\n";//第一行之前不输出空行

        cout << f[n]  << endl;
        //cin.get();
    }
}

