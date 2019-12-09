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

int n, m;
int head[310];
int ind;//边编号
int flag;

struct edge
{
    int cap,flow;//cap为容量，flow为流量
    int from,to;//一条边的起点终点
    int next;//和这条边起点相同的下一条边（邻接表标志）
}edges[100010];

void buildEdge(int u, int v, int z){
    edges[ind].from = u;
    edges[ind].to = v;
    edges[ind].cap = z;
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

//增广路算法
int bfs(){
    std::queue<int> Q;
    int min_flow[100010];
    memset(min_flow, 0, sizeof(min_flow));

    //从超级源点开始
    Q.push(1);
    min_flow[1] = INT_MAX;

    //记录路径，以便回溯更改边的flow
    int p[100010];
    p[1] = -1;

    while(!Q.empty()){
        int cur = Q.front();
        Q.pop();
        //遍历cur节点的所有边
        for(int e=head[cur]; e!=-1; e=edges[e].next){
            //残量
            int v = edges[e].cap - edges[e].flow;
            //当前边残量大于0,且to节点没有到达过
            if(v>0 && !min_flow[edges[e].to]){
                min_flow[edges[e].to] = std::min(v, min_flow[cur]);
                p[edges[e].to] = e; //记录达到此点的边的编号
                Q.push(edges[e].to);
            }
        }
        if(min_flow[m]) break;
    }
    if(min_flow[m] == 0)
        flag = 1;
    //e是节点号，从终点开始回溯
    for(int e=m; p[e]!=-1; e=edges[p[e]].from){
        edges[p[e]].flow += min_flow[m];
        edges[p[e]^1].flow -= min_flow[m];
    }

    return min_flow[m];
}

int maxFlow(){
    int max_flow(0);
    while(1){
        max_flow += bfs();
        if(flag) break;
    }

    return max_flow;
}

int main(){
    while(cin>>n>>m){
        //初始化
        ind=0;
        memset(head, -1, sizeof(head));
        flag=0;

        for(int i=1;i<=n;i++)//读入，构造邻接表
        {
            int a,b,c;
            cin>>a>>b>>c;
            buildEdge(a,b,c);
        }
        cout<<maxFlow()<<endl;//输出答案
    }
}
