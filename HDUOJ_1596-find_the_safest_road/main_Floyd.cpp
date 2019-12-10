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
#include <list>
#include <queue>
#include <utility>
#include <functional>

using std::pair;
using std::make_pair;
using std::priority_queue;
using std::list;
using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::greater;

//TLE
void Floyd(vector<vector<double> >& roads, int n){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            for(int k=0; k<n; ++k){
                if(roads[i][j] < roads[i][k]*roads[k][j]){
                    roads[i][j] = roads[i][k]*roads[k][j];
                }
            }
        }
    }
}

int main(){
    int n;
    while(cin >> n){
        vector<vector<double> > roads(n, vector<double>(n, 0.0));
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                cin >> roads[i][j];
            }
        }
        Floyd(roads, n);

        int Q;
        cin >> Q;
        while(Q--){
            int src, dest;
            cin >> src >> dest;
            if(fabs(roads[src-1][dest-1])<1e-9)
                cout << "What a pity!" << endl;
            else
                cout << std::fixed << std::setprecision(3) << roads[src-1][dest-1] << endl;
        }
    }
}
