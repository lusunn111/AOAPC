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

const int MAX_N = 500;
int ss, tt;//ss源点，tt汇点
int n, m;//n点数，m边数
int head[MAX_N];//点的第一条边
int ind;//边编号
int depth[MAX_N];//层次图节点深度
int cur[MAX_N];//记录当前节点循环到哪里

struct edge{
    //next为与edge同from的下一条边
    int from, to, next, cap;
    int flow = 0;
}edges[MAX_N];

void buildEdge(int u, int v, int w){
    edges[ind].from = u;
    edges[ind].to = v;
    edges[ind].cap = w;
    edges[ind].next = head[u];
    head[u] = ind;
    ++ind;
    edges[ind].from = v;
    edges[ind].to = u;
    edges[ind].cap = 0;
    edges[ind].next = head[v];
    head[v] = ind;
    ++ind;
}

void init(){
    ss=1;
    tt=n;
    memset(head, -1, sizeof(head));
    memset(edges, 0, sizeof(edges));
    ind = 0;
}

bool bfs(int s, int t){
    queue<int> Q;
    Q.push(s);
    memset(depth, 0, sizeof(depth));
    depth[s] = 1;
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        for(int e=head[u]; e!=-1; e=edges[e].next){
            //残量大于0,且to没有访问过
            if(edges[e].cap-edges[e].flow>0 && !depth[edges[e].to]){
                depth[edges[e].to] = depth[u] + 1;
                Q.push(edges[e].to);
                if(edges[e].to==t) return true;
            }
        }
    }

    return false;
}

int dfs(int u, int flow){
    //到达汇点
    if(u==tt)
        return flow;
    //注意这里的&符号，这样i增加的同时也能改变cur[u]的值，达到记录当前弧的目的
    for(int &e=cur[u]; e!=-1; e=edges[e].next){
        //只找层次图的边且残量大于0
        if(depth[u]+1==depth[edges[e].to] && edges[e].cap-edges[e].flow!=0){
            int d = dfs(edges[e].to, min(flow, edges[e].cap-edges[e].flow));
            //存在层次图中的增广路
            if(d>0){
                edges[e].flow += d;
                edges[e^1].flow -= d;
                return d;
            }
        }
    }
    return 0;//没有增广路
}

int maxFlow(int s, int t){
    int max_flow = 0;
    while(bfs(s, t)){
        //每一次建立完分层图后都要把cur置为每一个点的第一条边
        for(int i=ss; i<=tt; ++i){
            cur[i] = head[i];
        }
        while(int d = dfs(1, INT_MAX))
            max_flow += d;
    }
    return max_flow;
}

int main(){
    while(cin>>m>>n){
        init();

        int u, v, w;
        for(int i=0; i<m; ++i){
            cin >> u >> v >> w;
            buildEdge(u, v, w);
        }

        cout << maxFlow(ss, tt) << endl;
    }
}
