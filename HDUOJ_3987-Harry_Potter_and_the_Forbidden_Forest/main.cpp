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

using std::queue;
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

//增广法TLE
const int MAX_M = 400010;//设为100010就不能AC，题目明明说m小于等于100000啊
const int MAX_N = 1010;

struct edge{
    int from, to, flow, cap, next;
}edges[MAX_M];
int head[MAX_N];
int ind;//index of edges
int depth[MAX_N];
int cur[MAX_N];

int num_of_cases;
int n, m;//n is the number of nodes and m is the number of edges of the graph

void init(){
    ind = 0;
    memset(head, -1, sizeof(head));
    memset(edges, 0, sizeof(edges));
}

void buildEdge(int u, int v, int c){
    edges[ind].from = u;
    edges[ind].to = v;
    edges[ind].cap = c;
    edges[ind].flow = 0;
    edges[ind].next = head[u];
    head[u] = ind;
    ++ind;
    edges[ind].from = v;
    edges[ind].to = u;
    edges[ind].cap = 0;
    edges[ind].flow = 0;
    edges[ind].next = head[v];
    head[v] = ind;
    ++ind;
}

int bfs(){
    queue<int> Q;
    Q.push(0);
    memset(depth, 0, sizeof(depth));
    depth[0] = 1;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(int e=head[u]; e!=-1; e=edges[e].next){
            if(edges[e].cap-edges[e].flow>0 && !depth[edges[e].to]){
                depth[edges[e].to] = depth[u] + 1;
                Q.push(edges[e].to);
                if(edges[e].to==n-1) return 1;
            }
        }
    }
    return 0;
}

int dfs(int u, int flow){
    if(u==n-1)
        return flow;
    for(int &e=cur[u]; e!=-1; e=edges[e].next){
        if(depth[edges[e].to]==1+depth[u] && edges[e].cap-edges[e].flow>0){
            int d = dfs(edges[e].to, min(flow, edges[e].cap-edges[e].flow));
            if(d>0){
                edges[e].flow += d;
                edges[e^1].flow -= d;
                return d;
            }
        }
    }
    return 0;
}

int maxFlow(){
    int ans = 0;
    while(bfs()){
        for(int i=0; i<=n-1; ++i){
            cur[i] = head[i];
        }
        while(int d=dfs(0, INT_MAX))
            ans += d;
    }
    return ans;
}

int main(){
    cin >> num_of_cases;
    int k = 1;
    while(k<=num_of_cases){
        init();
        cin >> n >> m;
        for(int i=0; i<m; ++i){
            int u, v, c, d;
            cin >> u >> v >> c >> d;
            buildEdge(u, v, c);
            //undirected
            if(d)
                buildEdge(v, u, c);
        }

        maxFlow();
        for(int i=0; i<ind; i+=2){
            if(edges[i].cap==edges[i].flow){
                edges[i].cap = 1;
                edges[i].flow = 0;
            }else{
                edges[i].cap = INT_MAX;
                edges[i].flow = 0;
            }
            edges[i^1].cap = edges[i^1].flow = 0;
        }

        cout << "Case " << k << ": " << maxFlow() << endl;
        ++k;
    }
}
