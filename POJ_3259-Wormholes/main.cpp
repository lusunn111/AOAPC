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

struct edge{
    int s, e, t;
};

int Bellman_Ford(vector<edge>& edges, int N){
    vector<int> d(N+1, INT_MAX);
    d[1] = 0;
    //不含环的最短路径最多包含N-1个节点（不含起点）
    //首先算出到每个点的不含环的最短路径
    for(int i=0; i<N-1; ++i){
        for(int j=0; j<edges.size(); ++j){
            int u = edges[j].s, v = edges[j].e;
            //注意可能溢出
            if(d[u]!=INT_MAX && d[u]+edges[j].t < d[v]){
                d[v] = d[u]+edges[j].t;
            }
        }
    }

    //接着找是否存在负环
    for(int i=0; i<edges.size(); ++i){
        int u = edges[i].s, v = edges[i].e;
        //d已经是不含环的最小路径，如果还存在更小路径，一定是含负环
        if(d[u]+edges[i].t < d[v]) return 1;
    }

    return 0;
}

int main(){
    int F;
    cin >> F;
    while(F--){
        //建边
        int N, M, W;
        cin >> N >> M >> W;
        int S, E, T;
        vector<edge> edges(2*M+W);
        for(int i=0; i<2*M;){
            cin >> S >> E >> T;
            edges[i].s = S;
            edges[i].e = E;
            edges[i].t = T;
            ++i;
            edges[i].s = E;
            edges[i].e = S;
            edges[i].t = T;
            ++i;
        }
        for(int i=2*M; i<2*M+W; ++i){
            cin >> S >> E >> T;
            edges[i].s = S;
            edges[i].e = E;
            edges[i].t = -1*T;
        }

        int flag = Bellman_Ford(edges, N);
        if(flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
