#include <iostream>
#include <cstring>
#include <cfloat>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::fabs;

int n;
constexpr int MAX_M = 50;
int m;

class point{
public:
    int x;
    int y;
    point(int x, int y){
        this->x = x;
        this->y = y;
    }
};

vector<point> vertex;
vector<vector<double> > dp;

double area(point& p0, point& p1, point& p2){
    return std::abs(0.5*(p0.x*p1.y+p2.x*p0.y+p1.x*p2.y-p2.x*p1.y-p1.x*p0.y-p0.x*p2.y));//有向面积加abs
}

bool valid(int k, int i, int j){//为什么只看i，k，j内有没有点？
    double area1 = area(vertex[i], vertex[k], vertex[j]);
    for(int l=0; l<m; ++l) {
        if(l==k || l==i || l==j) continue;
        double area2 = area(vertex[i], vertex[k], vertex[l]);
        double area3 = area(vertex[i], vertex[j], vertex[l]);
        double area4 = area(vertex[k], vertex[j], vertex[l]);
        if(fabs(area1-area2-area3-area4)<1e-9) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n;
    while(n--){
        vertex.clear();
        cin >> m;
        for(int i=0; i<m; ++i){
            int x, y;
            cin >> x >> y;
            vertex.emplace_back(x, y);
        }

        dp.assign(MAX_M, vector<double>(MAX_M, DBL_MAX));
        for(int delta=0; delta<m; ++delta){ //长区间依赖短区间
            for(int i=0; i<m-delta; ++i){
                if(delta==0 || delta==1){
                    dp[i][i+delta] = 0;
                }else{
                    for(int k=i+1; k<i+delta; ++k){
                        if(valid(k, i, i+delta)){
                            dp[i][i+delta] = min(dp[i][i+delta], max(area(vertex[i], vertex[k], vertex[i+delta]), max(dp[i][k], dp[k][i+delta])));
                        }
                    }
                }
            }
        }

        cout << std::fixed << std::setprecision(1) << dp[0][m-1] << endl;
    }
}

