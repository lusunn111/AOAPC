#include <iostream>
#include <cstring>
#include <cfloat>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <map>
#include <jmorecfg.h>
#include <numeric>

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;

constexpr int MAX_N = 8;
int N;
int x[2*MAX_N];
int y[2*MAX_N];
double d[100000];//大小起码要1<<2N

double dist(int i, int j){
    int length = abs(x[i]-x[j]);
    int width = abs(y[i]-y[j]);
    return std::sqrt(length*length+width*width);
}

int main() {
    int cnt(0);
    while(cin >> N && N!=0){
        ++cnt;
        for(int i=0; i<2*N; ++i){
            string name;
            cin >> name;
            cin >> x[i] >> y[i];
        }
        N *= 2;
        d[0] = 0;
        for(int S=1; S<(1<<N); ++S){
            d[S] = DBL_MAX;
            int i, j;
            for(i=0; i<N; ++i){
                if(S & (1<<i)) break;
            }
            for(j=i+1; j<N; ++j){
                if(S & (1<<j)){
                    d[S] = min(d[S], dist(i, j)+d[S^(1<<i)^(1<<j)]);
                }
            }
        }

        cout << "Case " << cnt << ": " << std::fixed << std::setprecision(2) << d[(1<<N)-1] << endl;
    }
}

