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

int dijkstra(vector<vector<int> >& roads, int N){
    vector<int> d(N+1, INT_MAX);
    vector<int> vis(N+1, 0);
    d[1] = 0;
    for(int k=1; k<=N; ++k){
        int min_ind, min = INT_MAX;
        //找出路径最小点
        for(int i=1; i<=N; ++i){
            if(!vis[i] && d[i]<min){
                min = d[i];
                min_ind = i;
            }
        }
        vis[min_ind] = 1;
        //从路径最小点出发，计算其他点的路径
        for(int i=1; i<=N; ++i){
            if(!vis[i] && roads[min_ind][i]!=INT_MAX && d[min_ind]+roads[min_ind][i] < d[i]){
                d[i] = std::min(d[i], d[min_ind]+roads[min_ind][i]);
            }
        }
    }

    return d[N];
}

int main(){
    int N, M;
    while(cin>>N>>M && N!=0 && M!=0){
        //没有0号路口
        vector<vector<int> > roads(N+1, vector<int>(N+1, INT_MAX));
        for(int i=1; i<=N; ++i) roads[i][i] = 0;
        int A, B, C;
        for(int i=0; i<M; ++i){
            cin >> A >> B >> C;
            roads[A][B] = C;
            roads[B][A] = C;
        }

        cout << dijkstra(roads, N) << endl;
    }
}
