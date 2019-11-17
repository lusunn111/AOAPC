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

double P(int n, int m){
    double possibility(1.0);
    for(int i=0; i<m; ++i){
        possibility = possibility / static_cast<double>(n)* static_cast<double>(n-i);
    }
    return 1.0-possibility;
}

int main() {
    int T;
    cin >> T;
    int cases(0);
    while(cases++!=T){
        int n;
        cin >> n;
        int i;
        for(i=1; ; ++i){
            double possibility = P(n, i);
            if(possibility>=0.5) break;
        }
        cout << "Case " << cases << ": " << i-1 << endl; //输出的是邀请的人数，不包含自己
    }
}
